/**
  ******************************************************************************
  * File Name          : delay.c
  * Description        : This file provides code for the configuration
  *                      of the delay instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "delay.h"
#include "os.h"

uint32_t DWT_Delay_Init(void)
{
    /* Disable TRC */
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    /* Enable TRC */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

    /* Disable clock cycle counter */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    /* Enable  clock cycle counter */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

    /* Reset the clock cycle counter value */
    DWT->CYCCNT = 0;

    /* 3 NO OPERATION instructions */
    __ASM volatile("NOP");
    __ASM volatile("NOP");
    __ASM volatile("NOP");

    /* Check if clock cycle counter has started */
    if (DWT->CYCCNT)
    {
        return 0; /*clock cycle counter started*/
    }
    else
    {
        return 1; /*clock cycle counter not started*/
    }
}

//us
void Sys_Delay_us(__IO uint32_t nTime)
{
    DWT_Delay_us(nTime);
}

//ms
void Sys_Delay_ms(uint32_t nTime)
{
    DWT_Delay_us(nTime * 1000);
}