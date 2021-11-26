#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"

extern TIM_HandleTypeDef htim2;
extern u32 Sys_Tick;

void MX_TIM2_Init(void);
u32 Sys_TickGetCount(void);

#ifdef __cplusplus
}
#endif
#endif