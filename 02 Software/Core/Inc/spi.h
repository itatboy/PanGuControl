#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"

extern SPI_HandleTypeDef hspi1;
void MX_SPI1_Init(void);
u8 SPI1_ReadWriteByte(u8 TxData);

#ifdef __cplusplus
}
#endif
#endif
