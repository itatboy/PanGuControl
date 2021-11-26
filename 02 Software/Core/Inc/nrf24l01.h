#ifndef __24L01_H
#define __24L01_H	 		  
#include "main.h"

#define NRF24L01_GPIO       GPIOD
#define NRF24L01_CS         9
#define NRF24L01_CE         10
#define NRF24L01_IRQ        PDin(11)

#define NRF24L01_CS_SET     NRF24L01_GPIO->BSRR=1<<NRF24L01_CS
#define NRF24L01_CS_CLR     NRF24L01_GPIO->BRR=1<<NRF24L01_CS
#define NRF24L01_CE_SET     NRF24L01_GPIO->BSRR=1<<NRF24L01_CE
#define NRF24L01_CE_CLR     NRF24L01_GPIO->BRR=1<<NRF24L01_CE

//NRF24L01寄存器操作命令
#define NRF_READ_REG    0x00  //读配置寄存器,低5位为寄存器地址
#define NRF_WRITE_REG   0x20  //写配置寄存器,低5位为寄存器地址
#define R_RX_PL_WID		  0x60	//读RX FIFO顶层R_RX_PLOAD载荷长度,若超出32字节则清除RX FIFO
#define RD_RX_PLOAD     0x61  //读RX有效数据,1~32字节
#define WR_TX_PLOAD     0xA0  //写TX有效数据,1~32字节
#define W_ACK_PAYLOAD	  0xA8  //RX模式下,通过PIPE PPP将数据通过ACK形式发送，最多允许三帧数据存在于FIFO。
#define FLUSH_TX        0xE1  //清除TX FIFO寄存器.发射模式下用
#define FLUSH_RX        0xE2  //清除RX FIFO寄存器.接收模式下用
#define REUSE_TX_PL     0xE3  //重新使用上一包数据,CE为高,数据包被不断发送.
#define NOP             0xFF  //空操作,可以用来读状态寄存器	 
//SPI(NRF24L01)寄存器地址
#define CONFIG          0x00  //配置寄存器地址
#define EN_AA           0x01  //使能自动应答功能  bit0~5,对应通道0~5  ;7~6保留
#define EN_RXADDR       0x02  //接收地址允许,     bit0~5,对应通道0~5  ;7~6保留
#define SETUP_AW        0x03  //设置地址宽度(所有数据通道):bit1~0, 00:无效;01(0x01):3字节;10(0x02):4字节;11(0x03):5字节;  ;7~2保留
#define SETUP_RETR      0x04  //bit7:4,自动重发延时 x:0-15  250*(x+1)+86us  255+86us----4000+86us
                              //bit3:0,自动重发计数器;0:禁止重发 1-15 重发1-15次
#define RF_CH           0x05  //RF通道,bit6:0,工作通道频率; 0-127  bit7保留
#define RF_SETUP        0x06  //RF寄存器;
                              //bit3:传输速率(0:1Mbps,1:2Mbps);
                              //bit2:1,发射功率;00:-18dbm  01:-12dbm 10:-6dbm 11:0dbm
                              //bit0:0:低噪声放大器增益关闭，1：开启
#define STATUS          0x07  //状态寄存器;
                              //bit6:接收数据中断
                              //bit5:数据发送完成中断;
                              //bit4,达到最多次重发
                              //bit3:1,接收数据通道号(最大:6);000-101:通道0-5  110:保留  111:RX_FIFO寄存器为空
                              //bit0:1:TX FIFO满标志;0:TX FIFO未满标志
#define OBSERVE_TX      0x08  //发送检测寄存器
#define CD              0x09  //载波检测寄存器,bit7-1保留；bit0,载波检测;
#define RX_ADDR_P0      0x0A  //数据通道0接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P1      0x0B  //数据通道1接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P2      0x0C  //数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P3      0x0D  //数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P4      0x0E  //数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P5      0x0F  //数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define TX_ADDR         0x10  //发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define RX_PW_P0        0x11  //接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P1        0x12  //接收数据通道1有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P2        0x13  //接收数据通道2有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P3        0x14  //接收数据通道3有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P4        0x15  //接收数据通道4有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P5        0x16  //接收数据通道5有效数据宽度(1~32字节),设置为0则非法
#define NRF_FIFO_STATUS 0x17  //FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留
                              //bit4,TX FIFO空标志;bit5,TX FIFO满标志;bit6,1,循环发送上一数据包.0,不循环;
#define DYNPD				    0x1C  // nRF24L01 Dynamic payload setup启用动态数据长度
															//5:DPL_P5  //4:DPL_P4  //3:DPL_P3  //2:DPL_P2  //1:DPL_P1  //0:DPL_P0
#define FEATURE			  	0x1D  // nRF24L01 Exclusive feature setup特征寄存器
															//2:EN_DPL   //1:EN_ACK_PAY  //0:EN_DYN_ACK															

//24L01发送接收数据宽度定义
#define TX_ADR_WIDTH    5   	//5字节的地址宽度
#define RX_ADR_WIDTH    5   	//5字节的地址宽度
#define TX_PLOAD_WIDTH  32  	//32字节的用户数据宽度
#define RX_PLOAD_WIDTH  32  	//32字节的用户数据宽度

extern u8 TX_ADDRESS[TX_ADR_WIDTH];//发送地址
extern u8 RX_ADDRESS[RX_ADR_WIDTH];//接收地址
extern u8 TX_BUF[TX_PLOAD_WIDTH];//发送缓存
extern u8 RX_BUF[TX_PLOAD_WIDTH];//接收缓存

extern u8 Ack_Data_Flag;//ACK接收标志
extern u8 Ack_Data_Read_Length; //读ACK数据长度

#define RX_OK   	    0x40  //接收到数据中断
#define TX_OK   	    0x20  //TX发送完成中断
#define MAX_TX  	    0x10  //达到最大发送次数中断
	
void NRF24L01_Init(void);	//初始化
u8 NRF24L01_Check(void);        //器件检测
void NRF24L01_TX_Mode(void);	//发送模式
void NRF24L01_RX_Mode(void);	//接收模式

/**
  * @brief  发送数据包
  * @param  pBuf: 数据 Len: 长度
  * @retval 发送结果
  */
u8 NRF24L01_TxPacket(u8 *pBuf, u8 Len);
/**
  * @brief  发送ACK包数据
  * @param  pBuf: 数据 Len: 长度
  */
void NRF24L01_PacketAckData(u8 *pBuf, u8 Len);
/**
  * @brief  接收数据包
  * @param  channel: 通道 length: 长度 rxbuf: 数据
  * @retval 接收结果
  */
u8 NRF24L01_RxPacket(u8 *channel, u8 *length, u8 *rxbuf);

u8 NRF24L01_Write_Reg(u8 reg,u8 value);//写寄存器命令
u8 NRF24L01_Read_Reg(u8 reg);//读寄存器命令
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);//写寄存器数据
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len);//读寄存器数据	
#endif
