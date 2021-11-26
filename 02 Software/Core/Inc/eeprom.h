#ifndef __EEPROM_H
#define __EEPROM_H
#include "main.h" 
 
u8 EERPOM_Check(void);
u8 EERPOM_ReadOneByte(u16 ReadAddr);
void EERPOM_WriteOneByte(u16 WriteAddr,u8 DataToWrite);

void EERPOM_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);
u32 EERPOM_ReadLenByte(u16 ReadAddr,u8 Len);

/**
  * @brief  �洢����
  * @param  SubAddress: ��ַ
  * @param  src: ����
  * @param  len: ����
  */
void Sys_EEPROM_WrBytes(u16 SubAddress,u8 *src,u8 len);

/**
  * @brief  ��ȡ����
  * @param  SubAddress: ��ַ
  * @param  dst: ����
  * @param  len: ����
  */
void Sys_EEPROM_RdBytes(u16 SubAddress,u8 *dst,u8 len);

#endif
