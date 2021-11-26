/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : This file provides code for the configuration
  *                      of the main instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "delay.h"
#include "eeprom.h"
#include "menu.h"
#include "lcd.h"
#include "nrf24l01.h"

u8 buf[32];

/**
  * @brief  Main program entry
  * @retval int
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    DWT_Delay_Init();
    MX_GPIO_Init();
    LCD_Init();
    MX_DMA_Init(); 
    MX_TIM2_Init();
    HAL_TIM_Base_Start_IT(&htim2);
    MX_ADC1_Init();
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc1_buf, (ADC_CNT * ADC_FRE));
    MX_SPI1_Init();
    NRF24L01_Init();
    while (EERPOM_Check())
    {
        GUI_StrCenterCh(0, 145, RED, BLACK, "存储初始化失败", 24, 0);
        Sys_Delay_ms(300);
    }
    while (NRF24L01_Check())
    {
        GUI_StrCenterCh(0, 145, RED, BLACK, "系统初始化失败", 24, 0);
        Sys_Delay_ms(300);
    }
    LCD_FillRectangle(160, 160, 320, 180, POINT_COLOR, FILL_MODE_LEFT);
    Thread();
    while (1)
    {
        NRF24L01_TxPacket(buf, 32);
        Sys_Delay_ms(300);
    }
}

/**
  * @brief System clock config
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&htim2))
    {
        Sys_Tick++;
    }
    if (htim->Instance == TIM3) 
    {
        HAL_IncTick();
    }
}

void Error_Handler(void)
{
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
