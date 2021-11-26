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

u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x66, 0x88, 0x00, 0x08, 0x20}; //���͵�ַ
u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x66, 0x88, 0x00, 0x08, 0x20}; //���յ�ַ
u8 TX_BUF[TX_PLOAD_WIDTH];                                    //���ͻ���
u8 RX_BUF[TX_PLOAD_WIDTH];                                    //���ջ���

u8 Ack_Data_Flag;             //ACK���ձ�־
u8 Ack_Data_Read_Length;      //��ACK���ݳ���

/**
  * @brief  ��ʼ��
  */
void NRF24L01_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOD_CLK_ENABLE();

    //CE��CS
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

    NRF24L01_CE_CLR;                                     //ʹ��
    NRF24L01_CS_SET;                                     //Ƭѡ
    NRF24L01_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);     //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(NRF_WRITE_REG + RF_CH, 40);       //����RFͨ��Ƶ��
    NRF24L01_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x0f);  //����TX�������,0db����,2Mbps,���������濪��
    NRF24L01_CE_SET;                                     //ʧ��
    
    NRF24L01_TX_Mode(); 
    Sys_Delay_ms(20);
}

/**
  * @brief  �������
  * @retval 0���ɹ� 1��ʧ��
  */
u8 NRF24L01_Check(void)
{
    u8 buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    u8 i;
    NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR, buf, 5); //д��5���ֽڵĵ�ַ.
    NRF24L01_Read_Buf(TX_ADDR, buf, 5);                  //����д��ĵ�ַ
    for (i = 0; i < 5; i++)
        if (buf[i] != 0XA5)
            break;
    if (i != 5)
        return 1;
    return 0;
}

/**
  * @brief  ����ģʽ
  */
void NRF24L01_TX_Mode(void)
{
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR, (u8 *)TX_ADDRESS, TX_ADR_WIDTH); //дTX�ڵ��ַ,��ҪΪ��ʹ��ACK
    NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);                            //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
    NRF24L01_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1a);                        //�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
    NRF24L01_Write_Reg(FLUSH_TX, 0xff);                                          //���TX FIFO�Ĵ���
    NRF24L01_Write_Reg(FLUSH_RX, 0xff);                                          //���RX FIFO�Ĵ���
    SPI1_ReadWriteByte(0x50);
    SPI1_ReadWriteByte(0x73);
    NRF24L01_Write_Reg(NRF_WRITE_REG + DYNPD, 0x01);   //ʹ��ͨ��1�Ķ�̬���ݿ��
    NRF24L01_Write_Reg(NRF_WRITE_REG + FEATURE, 0x07); //ʹ�ܶ�̬���ݿ�Ⱥʹ����ݰ�Ӧ��
    NRF24L01_CE_SET;
}

/**
  * @brief  ����ģʽ
  */
void NRF24L01_RX_Mode(void)
{
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8 *)RX_ADDRESS, RX_ADR_WIDTH); //дRX�ڵ��ַ,��ҪΪ��ʹ��ACK
    NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);                               //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
    NRF24L01_Write_Reg(FLUSH_TX, 0xff);                                             //���TX FIFO�Ĵ���
    NRF24L01_Write_Reg(FLUSH_RX, 0xff);                                             //���RX FIFO�Ĵ���
    SPI1_ReadWriteByte(0x50);
    SPI1_ReadWriteByte(0x73);
    NRF24L01_Write_Reg(NRF_WRITE_REG + DYNPD, 0x01);   //ʹ��ͨ��1�Ķ�̬���ݿ��
    NRF24L01_Write_Reg(NRF_WRITE_REG + FEATURE, 0x07); //ʹ�ܶ�̬���ݿ�Ⱥʹ����ݰ�Ӧ��
    NRF24L01_CE_SET;
}

/**
  * @brief  �������ݰ�
  * @param  pBuf: ���� Len: ����
  * @retval ���ͽ��
  */
u8 NRF24L01_TxPacket(u8 *pBuf, u8 Len)
{
    u8 sta;
    u8 return_temp = 0;
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(NRF_WRITE_REG | TX_ADDR, (u8 *)RX_ADDRESS, RX_ADR_WIDTH);    //0ͨ������
    NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8 *)TX_ADDRESS, TX_ADR_WIDTH); //����Ӧ��ʱװ��֡ͷ���Է��ģ���ַ
    NRF24L01_Write_Buf(WR_TX_PLOAD, pBuf, Len);
    NRF24L01_CE_SET;
    Sys_Delay_us(10);
    while (NRF24L01_IRQ != 0); //�ȴ��������
    sta = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);  //��״̬�Ĵ���
    NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, sta); //���RX_DS�жϱ�־
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
        Ack_Data_Read_Length = NRF24L01_Read_Reg(NRF_READ_REG + R_RX_PL_WID); //��ȡACK����
        if (Ack_Data_Read_Length < 33)
        {
            NRF24L01_Read_Buf(RD_RX_PLOAD, RX_BUF, Ack_Data_Read_Length); //��RXFIFO��������
            Ack_Data_Flag = 1;                                            //����־λ��1����ʾ���յ����ݣ�����������ȥ������յ�������
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
  * @brief  ����ACK������
  * @param  pBuf: ���� Len: ����
  */
void NRF24L01_PacketAckData(u8 *pBuf, u8 Len)
{
    NRF24L01_CE_CLR;
    NRF24L01_Write_Buf(W_ACK_PAYLOAD, pBuf, Len);
    NRF24L01_CE_SET;
}

/**
  * @brief  �������ݰ�
  * @param  channel: ͨ�� length: ���� rxbuf: ����
  * @retval ���ս��
  */
u8 NRF24L01_RxPacket(u8 *channel, u8 *length, u8 *rxbuf)
{
    u8 sta;
    sta = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);  //��״̬�Ĵ���
    NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, sta); //?���RX_DS�жϱ�־
    if (sta & RX_OK)
    {
        *channel = (sta & 0x0e) >> 1;
        *length = NRF24L01_Read_Reg(NRF_READ_REG + R_RX_PL_WID);
        if (*length < 33)
        {
            NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, *length); //��RXFIFO��������
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
  * @brief  д�Ĵ�������
  * @param  reg: �Ĵ��� value: ֵ
  * @retval 
  */
u8 NRF24L01_Write_Reg(u8 reg, u8 value)
{
    u8 status;
    NRF24L01_CS_CLR;                  //ʹ��SPI1����
    status = SPI1_ReadWriteByte(reg); //���ͼĴ�����
    SPI1_ReadWriteByte(value);        //д��Ĵ�����ֵ
    NRF24L01_CS_SET;                  //ʧ��SPI1����
    return status;
}

/**
  * @brief  ���Ĵ�������
  * @param  reg: �Ĵ��� value: ֵ
  * @retval 
  */
u8 NRF24L01_Read_Reg(u8 reg)
{
    u8 reg_val;
    NRF24L01_CS_CLR;                    //ʹ��SPI1����
    SPI1_ReadWriteByte(reg);            //���ͼĴ�����
    reg_val = SPI1_ReadWriteByte(0XFF); //��ȡ�Ĵ�������
    NRF24L01_CS_SET;                    //ʧ��SPI1����
    return reg_val;
}

/**
  * @brief  д�Ĵ�������
  * @param  reg: �Ĵ��� pBuf: ���� len: ����
  * @retval 
  */
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
    u8 status, u8_ctr;
    NRF24L01_CS_CLR;                  //ʹ��SPI1����
    status = SPI1_ReadWriteByte(reg); //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        SPI1_ReadWriteByte(*pBuf++); //д������
    NRF24L01_CS_SET;                 //ʧ��SPI1����
    return status;
}

/**
  * @brief  ���Ĵ�������
  * @param  reg: �Ĵ��� pBuf: ���� len: ����
  * @retval 
  */
u8 NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
    u8 status, u8_ctr;
    NRF24L01_CS_CLR;                  //ʹ��SPI1����
    status = SPI1_ReadWriteByte(reg); //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        pBuf[u8_ctr] = SPI1_ReadWriteByte(0XFF); //��������
    NRF24L01_CS_SET;                             //ʧ��SPI1����
    return status;
}
