#ifndef __DELAY_H
#define __DELAY_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "main.h"
 
uint32_t DWT_Delay_Init(void);
 
__STATIC_INLINE void DWT_Delay_us(uint32_t microseconds)
{
  uint32_t clk_cycle_start = DWT->CYCCNT;
 
  /* Go to number of cycles for system */
  microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);
 
  /* Delay till end */
  while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}
 
#ifdef __cplusplus
}
#endif
 
void Sys_Delay_us(__IO uint32_t nTime);
void Sys_Delay_ms(uint32_t nTime);

#endif