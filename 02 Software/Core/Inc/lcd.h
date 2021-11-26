#ifndef __LCD_H
#define __LCD_H		
#include "main.h"	 

extern u16 POINT_COLOR;

typedef struct  
{										    
    u16 width;			
    u16 height;					
    u16	 wramcmd;		
    u16  rramcmd;                
    u16  setxcmd;		
    u16  setycmd;		
}_lcd_dev; 	
extern _lcd_dev lcddev;

#define LCD_W   240
#define LCD_H   320

#define USE_HORIZONTAL  	 1
 
#define GPIO_TYPE  GPIOB  
#define LCD_CS   6               
#define LCD_RS   5       
#define LCD_RST  7              
#define LCD_WR   4                    
#define LCD_RD   3              

#define	LCD_CS_SET      GPIO_TYPE->BSRR=1<<LCD_CS   	
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST 		  
#define	LCD_WR_SET	GPIO_TYPE->BSRR=1<<LCD_WR 
#define LCD_RD_SET      GPIO_TYPE->BSRR=1<<LCD_RD 	  
							    
#define	LCD_CS_CLR      GPIO_TYPE->BRR=1<<LCD_CS   
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST 		  
#define	LCD_WR_CLR	GPIO_TYPE->BRR=1<<LCD_WR   
#define LCD_RD_CLR      GPIO_TYPE->BRR=1<<LCD_RD 

#define DATAIN     GPIOB->IDR; 

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

void LCD_write(u8 data);
void LCD_WR_REG(u8 data);
void LCD_WR_DATA(u8 data);
void LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_WriteRAM_Prepare(void);

u16 LCD_read(void);
void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n);
u16 LCD_RD_DATA(void);	
u16 Lcd_ReadData_16Bit(void);
void LCD_ReadRAM_Prepare(void);
u16 Color_To_565(u8 r, u8 g, u8 b);

void LCD_Init(void); 
u16 LCD_Read_ID(void);
void LCD_RESET(void);
void LCD_Clear(u16 Color);
void LCD_direction(u8 direction );

/********************************************************************
    LCD API
 *******************************************************************/
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
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);

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

/**
  * @brief  Startup gui
  * @retval None
  */
void Startup_Animation(void);
#endif  
