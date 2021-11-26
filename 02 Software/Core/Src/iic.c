/**
  ******************************************************************************
  * File Name          : iic.c
  * Description        : This file provides code for the configuration
  *                      of the IIC instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "iic.h"
#include "delay.h"

void SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = IIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(IIC_SDA_GPIO_Port, &GPIO_InitStruct);
}

void SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = IIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(IIC_SDA_GPIO_Port, &GPIO_InitStruct);
}

void IIC1_Start(void)
{
    SDA_OUT();
    SDA_OUT_HIGH();
    SCL_OUT_HIGH();
    Sys_Delay_us(4);
    SDA_OUT_LOW();
    Sys_Delay_us(4);
    SCL_OUT_LOW();
}

void IIC1_Stop(void)
{
    SDA_OUT();
    SCL_OUT_LOW();
    SDA_OUT_LOW();
    Sys_Delay_us(4);
    SCL_OUT_HIGH();
    SDA_OUT_HIGH();
    Sys_Delay_us(4);
}

u8 IIC1_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    SDA_IN();
    SDA_OUT_HIGH();
    Sys_Delay_us(2);
    SCL_OUT_HIGH();
    Sys_Delay_us(2);
    while (SDA_READ())
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            IIC1_Stop();
            return 1;
        }
    }
    SCL_OUT_LOW();
    return 0;
}

void IIC1_Ack(void)
{
    SCL_OUT_LOW();
    SDA_OUT();
    SDA_OUT_LOW();
    Sys_Delay_us(2);
    SCL_OUT_HIGH();
    Sys_Delay_us(2);
    SCL_OUT_LOW();
}

void IIC1_NAck(void)
{
    SCL_OUT_LOW();
    SDA_OUT();
    SDA_OUT_HIGH();
    Sys_Delay_us(2);
    SCL_OUT_HIGH();
    Sys_Delay_us(2);
    SCL_OUT_LOW();
}

void IIC1_Send_Byte(u8 txd)
{
    u8 t;
    SDA_OUT();
    SCL_OUT_LOW();
    for (t = 0; t < 8; t++)
    {
        if (txd & 0x80)
            SDA_OUT_HIGH();
        else
            SDA_OUT_LOW();

        txd <<= 1;
        Sys_Delay_us(2);
        SCL_OUT_HIGH();
        Sys_Delay_us(2);
        SCL_OUT_LOW();
        Sys_Delay_us(2);
    }
}

u8 IIC1_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN();
    for (i = 0; i < 8; i++)
    {
        SCL_OUT_LOW();
        Sys_Delay_us(2);
        SCL_OUT_HIGH();
        receive <<= 1;
        if (SDA_READ())
            receive++;
        Sys_Delay_us(1);
    }
    if (!ack)
        IIC1_NAck();
    else
        IIC1_Ack();
    return receive;
}
