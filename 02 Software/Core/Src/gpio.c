/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "gpio.h"
#include "tim.h"

void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOE, LCD_D2_Pin | LCD_D3_Pin | LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin | LCD_D0_Pin | LCD_D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LCD_RD_Pin | LCD_WR_Pin | LCD_RS_Pin | LCD_CS_Pin | LCD_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, IIC_SCL_Pin | IIC_SDA_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin =  KEY_DOWN_Pin | KEY_UP_Pin | KEY_ENTER_Pin | KEY_BACK_Pin | USB_OK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_D2_Pin | LCD_D3_Pin | LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin | LCD_D0_Pin | LCD_D1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BUZZER_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SWITCH_1_Pin | SWITCH_2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = SWITCH_3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USB_EN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RD_Pin | LCD_WR_Pin | LCD_RS_Pin | LCD_CS_Pin | LCD_RST_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = IIC_SCL_Pin | IIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void Sys_Pin_Ctrl(u8 Dev, u8 Status, u8 Colour)
{
    switch (Dev)
    {
    case BUZZER:
        if (!Status)
            HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
        else
            HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
        break;
    case USB_EN:
        if (!Status)
        {
            HAL_GPIO_WritePin(USB_EN_GPIO_Port, USB_EN_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(USB_EN_GPIO_Port, USB_EN_Pin, GPIO_PIN_SET);
        }
        break;
    }
}

u8 Sys_Pin_Get(u8 Switch)
{
    u8 ret = 0;
    switch (Switch)
    {
    case SWITCH1:
        ret = HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port, SWITCH_1_Pin);
        break;
    case SWITCH2:
        ret = HAL_GPIO_ReadPin(SWITCH_2_GPIO_Port, SWITCH_2_Pin);
        break;
    case SWITCH3:
        ret = HAL_GPIO_ReadPin(SWITCH_3_GPIO_Port, SWITCH_3_Pin);
        break;
    default:
        break;
    }
    return ret;
}

u8 Sys_ReadPin_Up(void)
{
    return HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin);
}
u8 Sys_ReadPin_Down(void)
{
    return HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin);
}
u8 Sys_ReadPin_Enter(void)
{
    return HAL_GPIO_ReadPin(KEY_ENTER_GPIO_Port, KEY_ENTER_Pin);
}
u8 Sys_ReadPin_Back(void)
{
    return HAL_GPIO_ReadPin(KEY_BACK_GPIO_Port, KEY_BACK_Pin);
}
