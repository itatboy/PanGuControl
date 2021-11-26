#ifndef __gpio_H
#define __gpio_H

#include "main.h"

void MX_GPIO_Init(void);
void Sys_Pin_Ctrl(u8 Dev, u8 Status, u8 Colour);
u8 Sys_Pin_Get(u8 Switch);

u8 Sys_ReadPin_Up(void);
u8 Sys_ReadPin_Down(void);
u8 Sys_ReadPin_Left(void);
u8 Sys_ReadPin_Right(void);
u8 Sys_ReadPin_Menu(void);
u8 Sys_ReadPin_Ok(void);
u8 Sys_ReadPin_Back(void);
u8 Sys_ReadPin_None(void);

#endif
