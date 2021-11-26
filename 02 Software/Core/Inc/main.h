#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f1xx_hal.h"

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define PITCH_Pin GPIO_PIN_0
#define PITCH_GPIO_Port GPIOC
#define YAW_Pin GPIO_PIN_1
#define YAW_GPIO_Port GPIOC
#define ROLL_Pin GPIO_PIN_2
#define ROLL_GPIO_Port GPIOC
#define THROTTLE_Pin GPIO_PIN_3
#define THROTTLE_GPIO_Port GPIOC
#define VOLTAGE_Pin GPIO_PIN_4
#define VOLTAGE_GPIO_Port GPIOC

#define KEY_UP_Pin GPIO_PIN_3
#define KEY_UP_GPIO_Port GPIOA
#define KEY_DOWN_Pin GPIO_PIN_2
#define KEY_DOWN_GPIO_Port GPIOA
#define KEY_ENTER_Pin GPIO_PIN_1
#define KEY_ENTER_GPIO_Port GPIOA
#define KEY_BACK_Pin GPIO_PIN_0
#define KEY_BACK_GPIO_Port GPIOA

#define LCD_D2_Pin GPIO_PIN_7
#define LCD_D2_GPIO_Port GPIOE
#define LCD_D3_Pin GPIO_PIN_8
#define LCD_D3_GPIO_Port GPIOE
#define LCD_D4_Pin GPIO_PIN_9
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_10
#define LCD_D5_GPIO_Port GPIOE
#define LCD_D6_Pin GPIO_PIN_11
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D7_Pin GPIO_PIN_12
#define LCD_D7_GPIO_Port GPIOE
#define LCD_D0_Pin GPIO_PIN_13
#define LCD_D0_GPIO_Port GPIOE
#define LCD_D1_Pin GPIO_PIN_14
#define LCD_D1_GPIO_Port GPIOE

#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOD

#define SWITCH_1_Pin GPIO_PIN_11
#define SWITCH_1_GPIO_Port GPIOB
#define SWITCH_2_Pin GPIO_PIN_10
#define SWITCH_2_GPIO_Port GPIOB
#define SWITCH_3_Pin GPIO_PIN_15
#define SWITCH_3_GPIO_Port GPIOE

#define USB_OK_Pin GPIO_PIN_10
#define USB_OK_GPIO_Port GPIOA
#define USB_EN_Pin GPIO_PIN_9
#define USB_EN_GPIO_Port GPIOA

#define LCD_RD_Pin GPIO_PIN_3
#define LCD_RD_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_4
#define LCD_WR_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_5
#define LCD_RS_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_7
#define LCD_RST_GPIO_Port GPIOB

#define IIC_SCL_Pin GPIO_PIN_0
#define IIC_SCL_GPIO_Port GPIOE
#define IIC_SDA_Pin GPIO_PIN_1
#define IIC_SDA_GPIO_Port GPIOE

#define BUZZER                  1
#define USB_EN                  2

#define OFF                     0
#define ON                      1

#define SWITCH1                 1
#define SWITCH2                 2
#define SWITCH3                 3

#define PITCH                   0
#define YAW                     1
#define ROLL                    2
#define THROTTLE                3
#define VOLTAGE                 4

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

void SystemClock_Config(void);
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif
