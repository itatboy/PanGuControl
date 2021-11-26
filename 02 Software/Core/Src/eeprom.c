/**
  ******************************************************************************
  * File Name          : eeprom.c
  * Description        : This file provides code for the configuration
  *                      of the EEPROM instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "eeprom.h"
#include "iic.h"
#include "delay.h"

u8 EERPOM_Check(void)
{
    u8 temp;
    temp = EERPOM_ReadOneByte(255);
    if (temp == 0X55)
        return 0;
    else
    {
        EERPOM_WriteOneByte(255, 0X55);
        temp = EERPOM_ReadOneByte(255);
        if (temp == 0X55)
            return 0;
    }
    return 1;
}

u8 EERPOM_ReadOneByte(u16 ReadAddr)
{
    u8 temp = 0;
    IIC1_Start();
    IIC1_Send_Byte(0XA0);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(ReadAddr >> 8);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(ReadAddr % 256);
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Send_Byte(0XA1);
    IIC1_Wait_Ack();
    temp = IIC1_Read_Byte(0);
    IIC1_Stop();
    return temp;
}

void EERPOM_WriteOneByte(u16 WriteAddr, u8 DataToWrite)
{
    IIC1_Start();
    IIC1_Send_Byte(0XA0);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(WriteAddr >> 8);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(WriteAddr % 256);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(DataToWrite);
    IIC1_Wait_Ack();
    IIC1_Stop();
    Sys_Delay_ms(6);
}

void EERPOM_WriteLenByte(u16 WriteAddr, u32 DataToWrite, u8 Len)
{
    u8 t;
    for (t = 0; t < Len; t++)
    {
        EERPOM_WriteOneByte(WriteAddr + t, (DataToWrite >> (8 * t)) & 0xff);
    }
}

u32 EERPOM_ReadLenByte(u16 ReadAddr, u8 Len)
{
    u8 t;
    u32 temp = 0;
    for (t = 0; t < Len; t++)
    {
        temp <<= 8;
        temp += EERPOM_ReadOneByte(ReadAddr + Len - t - 1);
    }
    return temp;
}

void Sys_EEPROM_RdBytes(u16 SubAddress, u8 *dst, u8 len)
{
    while (len)
    {
        *dst++ = EERPOM_ReadOneByte(SubAddress++);
        len--;
    }
}

void Sys_EEPROM_WrBytes(u16 SubAddress, u8 *src, u8 len)
{
    while (len--)
    {
        EERPOM_WriteOneByte(SubAddress, *src);
        SubAddress++;
        src++;
    }
}
