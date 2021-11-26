/**
  ******************************************************************************
  * File Name          : nrf24l01.c
  * Description        : This file provides code for the configuration
  *                      of the nrf24l01 instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "nrf24l01.h"
#include "spi.h"
#include "delay.h"

u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x66, 0x88, 0x00, 0x08, 0x20}; //发送地址
u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x66, 0x88, 0x00, 0x08, 0x20}; //接收地址
u8 TX_BUF[TX_PLOAD_WIDTH];                                    //发送缓存
u8 RX_BUF[TX_PLOAD_WIDTH];                                    //接收缓存

u8 Ack_Data_Flag;             //ACK接收标志
u8 Ack_Data_Read_Length;      //读ACK数据长度

/**
  * @brief  初始化
  */
void NRF24L01_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOD_CLK_ENABLE();

    //CE、CS
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    //IRQ
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_RESET);

    NRF24L01_CE_CLR;                                     //使能
    NRF24L01_CS_SET;                                     //片选
    NRF24L01_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);     //使能通道0的自动应答
    NRF24L01_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01); //使能通道0的接收地址
    NRF24L01_Write_Reg(NRF_WRITE_REG + RF_CH, 40);       //设置RF通信频率
    NRF24L01_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启
    NRF24L01_CE_SET;                                     //失能
    
    NRF24L01_TX_Mode(); 
    Sys_Delay_ms(20);
}

/**
  * @brief  器件检测
  * @retval 0：成功 1：失败
  */
u8 NRF24L01_Check(void)
{
    u8 buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    u8 i;
    NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR, buf, 5); //写入5个字节的地址.
    NRF24L01_Read_Buf(TX_ADDR, buf, 5);                  //读出写入的地址
    for (i = 0; i < 5; i++)
        if (buf[i] != 0XA5)
            break;
    if (i != 5)
        return 1;
    return 0;
}

/**
  * @brief  发送模式
  */
void NRF24L01_TX_Mode(void)
{
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR, (u8 *)TX_ADDRESS, TX_ADR_WIDTH); //写TX节点地址,主要为了使能ACK
    NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);                            //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
    NRF24L01_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1a);                        //设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
    NRF24L01_Write_Reg(FLUSH_TX, 0xff);                                          //清除TX FIFO寄存器
    NRF24L01_Write_Reg(FLUSH_RX, 0xff);                                          //清除RX FIFO寄存器
    SPI1_ReadWriteByte(0x50);
    SPI1_ReadWriteByte(0x73);
    NRF24L01_Write_Reg(NRF_WRITE_REG + DYNPD, 0x01);   //使能通道1的动态数据宽度
    NRF24L01_Write_Reg(NRF_WRITE_REG + FEATURE, 0x07); //使能动态数据宽度和带数据包应答
    NRF24L01_CE_SET;
}

/**
  * @brief  接收模式
  */
void NRF24L01_RX_Mode(void)
{
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8 *)RX_ADDRESS, RX_ADR_WIDTH); //写RX节点地址,主要为了使能ACK
    NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);                               //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
    NRF24L01_Write_Reg(FLUSH_TX, 0xff);                                             //清除TX FIFO寄存器
    NRF24L01_Write_Reg(FLUSH_RX, 0xff);                                             //清除RX FIFO寄存器
    SPI1_ReadWriteByte(0x50);
    SPI1_ReadWriteByte(0x73);
    NRF24L01_Write_Reg(NRF_WRITE_REG + DYNPD, 0x01);   //使能通道1的动态数据宽度
    NRF24L01_Write_Reg(NRF_WRITE_REG + FEATURE, 0x07); //使能动态数据宽度和带数据包应答
    NRF24L01_CE_SET;
}

/**
  * @brief  发送数据包
  * @param  pBuf: 数据 Len: 长度
  * @retval 发送结果
  */
u8 NRF24L01_TxPacket(u8 *pBuf, u8 Len)
{
    u8 sta;
    u8 return_temp = 0;
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(NRF_WRITE_REG | TX_ADDR, (u8 *)RX_ADDRESS, RX_ADR_WIDTH);    //0通道编码
    NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8 *)TX_ADDRESS, TX_ADR_WIDTH); //启用应答时装载帧头（对方的）地址
    NRF24L01_Write_Buf(WR_TX_PLOAD, pBuf, Len);
    NRF24L01_CE_SET;
    Sys_Delay_us(10);
    while (NRF24L01_IRQ != 0); //等待发送完成
    sta = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);  //读状态寄存器
    NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, sta); //清除RX_DS中断标志
    if (sta & TX_OK)
    {
        return_temp |= TX_OK;
    }
    if (sta & MAX_TX)
    {
        return_temp |= MAX_TX;
    }
    if (sta & RX_OK)
    {
        Ack_Data_Read_Length = NRF24L01_Read_Reg(NRF_READ_REG + R_RX_PL_WID); //获取ACK长度
        if (Ack_Data_Read_Length < 33)
        {
            NRF24L01_Read_Buf(RD_RX_PLOAD, RX_BUF, Ack_Data_Read_Length); //从RXFIFO读出数据
            Ack_Data_Flag = 1;                                            //将标志位置1，表示接收到数据，好让主函数去处理接收到的数据
        }
        else
        {
            NRF24L01_Write_Reg(FLUSH_RX, 0xff);
        }
        return return_temp |= RX_OK;
    }
    return return_temp;
}

/**
  * @brief  发送ACK包数据
  * @param  pBuf: 数据 Len: 长度
  */
void NRF24L01_PacketAckData(u8 *pBuf, u8 Len)
{
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(W_ACK_PAYLOAD, pBuf, Len);
    NRF24L01_CE_SET;
}

/**
  * @brief  接收数据包
  * @param  channel: 通道 length: 长度 rxbuf: 数据
  * @retval 接收结果
  */
u8 NRF24L01_RxPacket(u8 *channel, u8 *length, u8 *rxbuf)
{
    u8 sta;
    sta = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);  //读状态寄存器
    NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, sta); //?清除RX_DS中断标志
    if (sta & RX_OK)
    {
        *channel = (sta & 0x0e) >> 1;
        *length = NRF24L01_Read_Reg(NRF_READ_REG + R_RX_PL_WID);
        if (*length < 33)
        {
            NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, *length); //从RXFIFO读出数据
        }
        else
        {
            NRF24L01_Write_Reg(FLUSH_RX, 0xff);
        }
        return RX_OK;
    }
    return 0xff;
}

/**
  * @brief  写寄存器命令
  * @param  reg: 寄存器 value: 值
  * @retval 
  */
u8 NRF24L01_Write_Reg(u8 reg, u8 value)
{
    u8 status;
    NRF24L01_CS_CLR;                  //使能SPI1传输
    status = SPI1_ReadWriteByte(reg); //发送寄存器号
    SPI1_ReadWriteByte(value);        //写入寄存器的值
    NRF24L01_CS_SET;                  //失能SPI1传输
    return status;
}

/**
  * @brief  读寄存器命令
  * @param  reg: 寄存器 value: 值
  * @retval 
  */
u8 NRF24L01_Read_Reg(u8 reg)
{
    u8 reg_val;
    NRF24L01_CS_CLR;                    //使能SPI1传输
    SPI1_ReadWriteByte(reg);            //发送寄存器号
    reg_val = SPI1_ReadWriteByte(0XFF); //读取寄存器内容
    NRF24L01_CS_SET;                    //失能SPI1传输
    return reg_val;
}

/**
  * @brief  写寄存器数据
  * @param  reg: 寄存器 pBuf: 数据 len: 长度
  * @retval 
  */
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
    u8 status, u8_ctr;
    NRF24L01_CS_CLR;                  //使能SPI1传输
    status = SPI1_ReadWriteByte(reg); //发送寄存器值(位置),并读取状态值
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        SPI1_ReadWriteByte(*pBuf++); //写入数据
    NRF24L01_CS_SET;                 //失能SPI1传输
    return status;
}

/**
  * @brief  读寄存器数据
  * @param  reg: 寄存器 pBuf: 数据 len: 长度
  * @retval 
  */
u8 NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
    u8 status, u8_ctr;
    NRF24L01_CS_CLR;                  //使能SPI1传输
    status = SPI1_ReadWriteByte(reg); //发送寄存器值(位置),并读取状态值
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        pBuf[u8_ctr] = SPI1_ReadWriteByte(0XFF); //读出数据
    NRF24L01_CS_SET;                             //失能SPI1传输
    return status;
}
