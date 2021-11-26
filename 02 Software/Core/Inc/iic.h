#ifndef __IIC_H
#define __IIC_H
#include "main.h"

#define SDA_OUT_LOW()                      HAL_GPIO_WritePin(IIC_SDA_GPIO_Port,IIC_SDA_Pin,GPIO_PIN_RESET) 
#define SDA_OUT_HIGH()                     HAL_GPIO_WritePin(IIC_SDA_GPIO_Port,IIC_SDA_Pin,GPIO_PIN_SET)
#define SDA_READ()                         HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port,IIC_SDA_Pin)
#define SCL_OUT_LOW()                      HAL_GPIO_WritePin(IIC_SCL_GPIO_Port,IIC_SCL_Pin,GPIO_PIN_RESET) 
#define SCL_OUT_HIGH()                     HAL_GPIO_WritePin(IIC_SCL_GPIO_Port,IIC_SCL_Pin,GPIO_PIN_SET)

void SDA_OUT(void);
void SDA_IN(void);
void IIC1_Start(void);
void IIC1_Stop(void);
u8 IIC1_Wait_Ack(void);
void IIC1_Ack(void);
void IIC1_NAck(void);
void IIC1_Send_Byte(u8 txd);
u8 IIC1_Read_Byte(unsigned char ack);

#endif
