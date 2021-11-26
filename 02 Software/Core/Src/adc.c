/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "adc.h"

uint32_t adc1_buf[ADC_CNT * ADC_FRE];
uint32_t adc1_value[ADC_CNT] = {0};

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    /** Common config
  */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 5;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
  */
    sConfig.Channel = ADC_CHANNEL_10;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
  */
    sConfig.Channel = ADC_CHANNEL_11;
    sConfig.Rank = ADC_REGULAR_RANK_2;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
  */
    sConfig.Channel = ADC_CHANNEL_12;
    sConfig.Rank = ADC_REGULAR_RANK_3;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
  */
    sConfig.Channel = ADC_CHANNEL_13;
    sConfig.Rank = ADC_REGULAR_RANK_4;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
  */
    sConfig.Channel = ADC_CHANNEL_14;
    sConfig.Rank = ADC_REGULAR_RANK_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *adcHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (adcHandle->Instance == ADC1)
    {
        /* ADC1 clock enable */
        __HAL_RCC_ADC1_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        
        GPIO_InitStruct.Pin = PITCH_Pin | YAW_Pin | ROLL_Pin | THROTTLE_Pin | VOLTAGE_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        /* ADC1 DMA Init */
        /* ADC1 Init */
        hdma_adc1.Instance = DMA1_Channel1;
        hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
        hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
        hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
        hdma_adc1.Init.Mode = DMA_CIRCULAR;
        hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(adcHandle, DMA_Handle, hdma_adc1);

        /* ADC1 interrupt Init */
        HAL_NVIC_SetPriority(ADC1_2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
    }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef *adcHandle)
{

    if (adcHandle->Instance == ADC1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_ADC1_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOC, PITCH_Pin | YAW_Pin | ROLL_Pin | THROTTLE_Pin | VOLTAGE_Pin);

        /* ADC1 DMA DeInit */
        HAL_DMA_DeInit(adcHandle->DMA_Handle);

        /* ADC1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(ADC1_2_IRQn);
    }
}

u32 Sys_Adc_Get(u8 Switch)
{
    u8 i = 0;
    u32 value = 0;
    switch (Switch)
    {
    case PITCH:
        adc1_value[PITCH] = 0;
        for (i = 0; i < ADC_FRE; i++)
        {
            adc1_value[PITCH] += adc1_buf[i * ADC_CNT + PITCH];
        }
        value = adc1_value[PITCH] / ADC_FRE;
        return 3596 - value;
    case YAW:
        adc1_value[YAW] = 0;
        for (i = 0; i < ADC_FRE; i++)
        {
            adc1_value[YAW] += adc1_buf[i * ADC_CNT + YAW];
        }
        value = adc1_value[YAW] / ADC_FRE;
        return value;
    case ROLL:
        adc1_value[ROLL] = 0;
        for (i = 0; i < ADC_FRE; i++)
        {
            adc1_value[ROLL] += adc1_buf[i * ADC_CNT + ROLL];
        }
        value = adc1_value[ROLL] / ADC_FRE;
        return 3596 - value;
    case THROTTLE:
        adc1_value[THROTTLE] = 0;
        for (i = 0; i < ADC_FRE; i++)
        {
            adc1_value[THROTTLE] += adc1_buf[i * ADC_CNT + THROTTLE];
        }
        value = adc1_value[THROTTLE] / ADC_FRE;
        return value;
    case VOLTAGE:
        adc1_value[VOLTAGE] = 0;
        for (i = 0; i < ADC_FRE; i++)
        {
            adc1_value[VOLTAGE] += adc1_buf[i * ADC_CNT + VOLTAGE];
        }
        value = adc1_value[VOLTAGE] / ADC_FRE;
        return value;
    default:
        break;
    }
    return 0;
}
