#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

extern ADC_HandleTypeDef hadc1;

#define ADC_CNT                5 	//The channel number
#define ADC_FRE                10	//Single channel sampling times

#define PITCH              0
#define YAW                1
#define ROLL               2
#define THROTTLE           3
#define VOLTAGE            4

void MX_ADC1_Init(void);
extern uint32_t adc1_buf[ADC_CNT * ADC_FRE];
u32 Sys_Adc_Get(u8 Switch);

#ifdef __cplusplus
}
#endif
#endif
