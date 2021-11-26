/**
  ******************************************************************************
  * File Name          : api.h
  * Description        : This file provides code for the configuration
  *                      of the api instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#ifndef __API_H
#define __API_H
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "main.h"

/**
  * @brief  System initialization
  */
void Sys_Init(void);

/**
  * @brief  Get system count
  * @retval System count
  */
u32 Sys_TickGetCount(void);

/**
  * @brief  Microsecond delay
  * @param  nTime: us
  */
void Sys_Delay_us(uint32_t nTime);

/**
  * @brief  Millisecond delay
  * @param  nTime: ms
  */
void Sys_Delay_ms(uint32_t nTime);

/**
  * @brief  Set the user pin state
  * @param  Dev: User pin
  * @param  Status: state
  * @param  Colour: LED Colour
  */
void Sys_Pin_Ctrl(u8 Dev, u8 Status, u8 Colour);

/**
  * @brief  Gets the user's pin status
  * @param  Switch: User pin
  * @retval Returns the user pin state
  */
u8 Sys_Pin_Get(u8 Switch);

/**
  * @brief  For ADC values
  * @param  Switch: ADC channels
  * @retval Value
  */
u32 Sys_Adc_Get(u8 Switch);

/**
  * @brief  存储数据
  * @param  SubAddress: 地址
  * @param  src: 数据
  * @param  len: 长度
  */
void Sys_EEPROM_WrBytes(u16 SubAddress,u8 *src,u8 len);

/**
  * @brief  读取数据
  * @param  SubAddress: 地址
  * @param  dst: 数据
  * @param  len: 长度
  */
void Sys_EEPROM_RdBytes(u16 SubAddress,u8 *dst,u8 len);
/**
  * @brief  发送数据包
  * @param  pBuf: 数据 Len: 长度
  * @retval 发送结果
  */
u8 NRF24L01_TxPacket(u8 *pBuf, u8 Len);
/**
  * @brief  发送ACK包数据
  * @param  pBuf: 数据 Len: 长度
  */
void NRF24L01_PacketAckData(u8 *pBuf, u8 Len);
/**
  * @brief  接收数据包
  * @param  channel: 通道 length: 长度 rxbuf: 数据
  * @retval 接收结果
  */
u8 NRF24L01_RxPacket(u8 *channel, u8 *length, u8 *rxbuf);


/********************************************************************
    LCD API
 *******************************************************************/
#define FILL_MODE_UP    1
#define FILL_MODE_LEFT  2

#define WHITE       0xFFFF
#define BLACK       0x0000
#define RED         0xF800
#define BLUE        0x001F  
#define GREEN       0x07E0
#define YELLOW      0xFFE0
#define BRED        0XF81F
#define GRED 	    0XFFE0
#define GBLUE	    0X07FF
#define MAGENTA     0xF81F
#define CYAN        0x7FFF
#define BROWN 	    0XBC40
#define BRRED       0XFC07 
#define GRAY  	    0X8430 
#define DARKBLUE      	0X01CF	
#define LIGHTBLUE      	0X7D7C	
#define GRAYBLUE       	0X5458 
#define LIGHTGREEN     	0X841F 
#define LIGHTGRAY       0XEF5B 
#define LGRAY 		0XC618 
#define LGRAYBLUE      	0XA651 
#define LBBLUE          0X2B12 
/**
  * @brief  Lcd windows size set
  * @retval None
  */
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

/**
  * @brief  Lcd cursor set
  * @retval None
  */
void LCD_SetCursor(u16 Xpos, u16 Ypos);

/**
  * @brief  Set designated spot color
  * @retval None
  */
void LCD_DrawPoint(u16 x, u16 y,u16 point_color);

/**
  * @brief  Get designated spot color
  * @retval color
  */
u16  LCD_ReadPoint(u16 x,u16 y);

/**
  * @brief  Draw line
  * @retval None
  */
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/**
  * @brief  Draw rectangle
  * @retval None
  */
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/**
  * @brief  Fill rectangle
  * @retval None
  */
void LCD_FillRectangle(u16 sx, u16 sy, u16 ex, u16 ey,  u16 color, u8 mode);

/**
  * @brief  Draw circle
  * @retval None
  */
void _draw_circle_8(int xc, int yc, int x, int y, u16 c);

/**
  * @brief  Draw circle (fill or no fill)
  * @retval None
  */
void gui_circle(int xc, int yc, u16 c, int r, int fill);

/**
  * @brief  Draw triangel
  * @retval None
  */
void Draw_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/**
  * @brief  Fill triangel
  * @retval None
  */
void Fill_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2);

/**
  * @brief  Displays chinese and english string
  * @retval None
  */
void GUI_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);

/**
  * @brief  Displays english string center
  * @retval None
  */
void GUI_StrCenterEn(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);

/**
  * @brief  Displays chinese string center
  * @retval None
  */
void GUI_StrCenterCh(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);

/**
  * @brief  Displays specified size image
  * @retval None
  */
void GUI_Drawbmp16(u16 x, u16 y, u16 width, u16 height, const unsigned char *p);

/********************************************************************
    OS API
 *******************************************************************/
/**
  * @brief  Create task
  * @param  fn: name
  * @param  tid: none
  * @param  stacksize: Stack size
  */
void os_create(void * fn, int tid,int  stacksize);

/**
  * @brief  Start task
  */
void os_start(void);
						
/**
  * @brief  Os ms delay
  */
void os_delayTick(u32  delayTick);

u8 Sys_ReadPin_Up(void);
u8 Sys_ReadPin_Down(void);
u8 Sys_ReadPin_Enter(void);
u8 Sys_ReadPin_Back(void);

#endif