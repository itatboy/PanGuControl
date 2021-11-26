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

//NRF24L01�Ĵ�����������
#define NRF_READ_REG    0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define NRF_WRITE_REG   0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define R_RX_PL_WID		  0x60	//��RX FIFO����R_RX_PLOAD�غɳ���,������32�ֽ������RX FIFO
#define RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define W_ACK_PAYLOAD	  0xA8  //RXģʽ��,ͨ��PIPE PPP������ͨ��ACK��ʽ���ͣ����������֡���ݴ�����FIFO��
#define FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 
//SPI(NRF24L01)�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5  ;7~6����
#define EN_RXADDR       0x02  //���յ�ַ����,     bit0~5,��Ӧͨ��0~5  ;7~6����
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1~0, 00:��Ч;01(0x01):3�ֽ�;10(0x02):4�ֽ�;11(0x03):5�ֽ�;  ;7~2����
#define SETUP_RETR      0x04  //bit7:4,�Զ��ط���ʱ x:0-15  250*(x+1)+86us  255+86us----4000+86us
                              //bit3:0,�Զ��ط�������;0:��ֹ�ط� 1-15 �ط�1-15��
#define RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��; 0-127  bit7����
#define RF_SETUP        0x06  //RF�Ĵ���;
                              //bit3:��������(0:1Mbps,1:2Mbps);
                              //bit2:1,���书��;00:-18dbm  01:-12dbm 10:-6dbm 11:0dbm
                              //bit0:0:�������Ŵ�������رգ�1������
#define STATUS          0x07  //״̬�Ĵ���;
                              //bit6:���������ж�
                              //bit5:���ݷ�������ж�;
                              //bit4,�ﵽ�����ط�
                              //bit3:1,��������ͨ����(���:6);000-101:ͨ��0-5  110:����  111:RX_FIFO�Ĵ���Ϊ��
                              //bit0:1:TX FIFO����־;0:TX FIFOδ����־
#define OBSERVE_TX      0x08  //���ͼ��Ĵ���
#define CD              0x09  //�ز����Ĵ���,bit7-1������bit0,�ز����;
#define RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P1      0x0B  //����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P2      0x0C  //����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P3      0x0D  //����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P4      0x0E  //����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P5      0x0F  //����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_FIFO_STATUS 0x17  //FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
                              //bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
#define DYNPD				    0x1C  // nRF24L01 Dynamic payload setup���ö�̬���ݳ���
															//5:DPL_P5  //4:DPL_P4  //3:DPL_P3  //2:DPL_P2  //1:DPL_P1  //0:DPL_P0
#define FEATURE			  	0x1D  // nRF24L01 Exclusive feature setup�����Ĵ���
															//2:EN_DPL   //1:EN_ACK_PAY  //0:EN_DYN_ACK															

//24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH    5   	//5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5   	//5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  32  	//32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  32  	//32�ֽڵ��û����ݿ��

extern u8 TX_ADDRESS[TX_ADR_WIDTH];//���͵�ַ
extern u8 RX_ADDRESS[RX_ADR_WIDTH];//���յ�ַ
extern u8 TX_BUF[TX_PLOAD_WIDTH];//���ͻ���
extern u8 RX_BUF[TX_PLOAD_WIDTH];//���ջ���

extern u8 Ack_Data_Flag;//ACK���ձ�־
extern u8 Ack_Data_Read_Length; //��ACK���ݳ���

#define RX_OK   	    0x40  //���յ������ж�
#define TX_OK   	    0x20  //TX��������ж�
#define MAX_TX  	    0x10  //�ﵽ����ʹ����ж�
	
void NRF24L01_Init(void);	//��ʼ��
u8 NRF24L01_Check(void);        //�������
void NRF24L01_TX_Mode(void);	//����ģʽ
void NRF24L01_RX_Mode(void);	//����ģʽ

/**
  * @brief  �������ݰ�
  * @param  pBuf: ���� Len: ����
  * @retval ���ͽ��
  */
u8 NRF24L01_TxPacket(u8 *pBuf, u8 Len);
/**
  * @brief  ����ACK������
  * @param  pBuf: ���� Len: ����
  */
void NRF24L01_PacketAckData(u8 *pBuf, u8 Len);
/**
  * @brief  �������ݰ�
  * @param  channel: ͨ�� length: ���� rxbuf: ����
  * @retval ���ս��
  */
u8 NRF24L01_RxPacket(u8 *channel, u8 *length, u8 *rxbuf);

u8 NRF24L01_Write_Reg(u8 reg,u8 value);//д�Ĵ�������
u8 NRF24L01_Read_Reg(u8 reg);//���Ĵ�������
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);//д�Ĵ�������
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len);//���Ĵ�������	
#endif
