/**
  ******************************************************************************
  * File Name          : lcd.c
  * Description        : This file provides code for the configuration
  *                      of the LCD instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "lcd.h"
#include "stdlib.h"
#include "string.h"
#include "delay.h"
#include "font.h"

_lcd_dev lcddev;
u16 POINT_COLOR = 0xFFFF, BACK_COLOR = 0x0000;

u16 DeviceCode;

/*****************************************************************************
 * Write
******************************************************************************/
void LCD_Data_Out(u8 data)
{
    u16 dat=data&0X01;
    GPIOE->ODR&=~(0X1<<13);
    GPIOE->ODR|=dat<<13;
    
    GPIOE->ODR&=~(0X1<<14);
    GPIOE->ODR|=((data>>1)&0x01)<<14;

    GPIOE->ODR&=~(0X1<<7);		
    GPIOE->ODR|=((data>>2)&0x01)<<7;

    GPIOE->ODR&=~(0X1<<8);		
    GPIOE->ODR|=((data>>3)&0x01)<<8;
    
    GPIOE->ODR&=~(0X1<<9);		
    GPIOE->ODR|=((data>>4)&0x01)<<9;
    
    GPIOE->ODR&=~(0X1<<10);		
    GPIOE->ODR|=((data>>5)&0x01)<<10;
    
    GPIOE->ODR&=~(0X1<<11);		
    GPIOE->ODR|=((data>>6)&0x01)<<11;
    
    GPIOE->ODR&=~(0X1<<12);		
    GPIOE->ODR|=((data>>7)&0x01)<<12;
}

void LCD_write(u8 data)
{
    LCD_CS_CLR;
    LCD_Data_Out(data);
    LCD_WR_CLR;
    LCD_WR_SET;
    LCD_CS_SET;
}

void LCD_WR_REG(u8 data)
{
    LCD_RS_CLR;
    LCD_write(data);
}

void LCD_WR_DATA(u8 data)
{
    LCD_RS_SET;
    LCD_write(data);
}

void LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue)
{
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

void Lcd_WriteData_16Bit(u16 Data)
{
    LCD_RS_SET; 
    LCD_CS_CLR;
    LCD_Data_Out(Data>>8);
    LCD_WR_CLR; 
    LCD_WR_SET;
    LCD_Data_Out(Data);
    LCD_WR_CLR; 
    LCD_WR_SET;
    LCD_CS_SET;
}

void LCD_WriteRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.wramcmd);
}

/*****************************************************************************
 * Read
******************************************************************************/
u16 LCD_read(void)
{
    u16 data;
    LCD_CS_CLR;
    LCD_RD_CLR;
    Sys_Delay_us(1);
    data = DATAIN;
    LCD_RD_SET;
    LCD_CS_SET;
    return data;
}

void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n)
{
    LCD_WR_REG(LCD_Reg);
    GPIOB->CRL = 0X88888888;//input
    GPIOB->CRH = 0X88888888; 
    GPIOB->ODR = 0XFFFF; 
    while (n--)
    {
        *(Rval++) = LCD_RD_DATA();
    }
    GPIOB->CRL = 0X33333333;//out
    GPIOB->CRH = 0X33333333; 
    GPIOB->ODR = 0XFFFF;   
}

u16 LCD_RD_DATA(void)
{
    LCD_RS_SET;
    return (LCD_read() >> 8);
}

u16 Lcd_ReadData_16Bit(void)
{
    u16 r, g, b;
    LCD_RS_SET;
    LCD_CS_CLR;

    //dummy data
    LCD_RD_CLR;
    Sys_Delay_us(1);
    r = DATAIN;
    LCD_RD_SET;

    //8bit:red data
    //16bit:red and green data
    LCD_RD_CLR;
    Sys_Delay_us(1);
    r = DATAIN;
    LCD_RD_SET;

    //8bit:green data
    //16bit:blue data
    LCD_RD_CLR;
    Sys_Delay_us(1);
    g = DATAIN;
    LCD_RD_SET;
    
    //blue data
    LCD_RD_CLR;
    Sys_Delay_us(1);
    b = DATAIN;
    LCD_RD_SET;
    r >>= 8;
    g >>= 8;
    b >>= 8;
    LCD_CS_SET;
    return Color_To_565(r, g, b);
}

void LCD_ReadRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.rramcmd);
}

u16 Color_To_565(u8 r, u8 g, u8 b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

/*****************************************************************************
 * Basic
******************************************************************************/
/**
  * @brief  Lcd init
  * @retval None
  */
void LCD_Init(void)
{
    LCD_RESET();
    
    LCD_WR_REG(0xCF);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x81);
    LCD_WR_DATA(0x30);
    
    LCD_WR_REG(0xED);
    LCD_WR_DATA(0x64);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x81);
    
    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x85);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x78);

    LCD_WR_REG(0xCB);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x34);
    LCD_WR_DATA(0x02);
    
    LCD_WR_REG(0xF7);
    LCD_WR_DATA(0x20);

    LCD_WR_REG(0xEA);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x1B);

    LCD_WR_REG(0xB6);
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0xA2);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA(0x35);

    LCD_WR_REG(0xC1);
    LCD_WR_DATA(0x11);

    LCD_WR_REG(0xC5);
    LCD_WR_DATA(0x45);
    LCD_WR_DATA(0x45);

    LCD_WR_REG(0xC7);
    LCD_WR_DATA(0xa2);
    
    LCD_WR_REG(0xF2);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0x26);
    LCD_WR_DATA(0x01);
    //SET GAMMA
    LCD_WR_REG(0xE0);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x26);
    LCD_WR_DATA(0x24);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x54);
    LCD_WR_DATA(0xA8);
    LCD_WR_DATA(0x46);
    LCD_WR_DATA(0x0C);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x00);
    
    LCD_WR_REG(0xE1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0x1B);
    LCD_WR_DATA(0x04);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x2A);
    LCD_WR_DATA(0x47);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x30);
    LCD_WR_DATA(0x38);
    LCD_WR_DATA(0x0F);
    
    LCD_WR_REG(0x36);
    LCD_WR_DATA(0xC8);

    LCD_WR_REG(0x2A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xEF);

    LCD_WR_REG(0x2B);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x3F);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x55);

    LCD_direction(USE_HORIZONTAL);
    LCD_Clear(BLACK);
    
    LCD_WR_REG(0x11);
    Sys_Delay_ms(120);
    LCD_WR_REG(0x29);
   
    Startup_Animation();
}

/**
  * @brief  Get lcd id
  * @retval LCD ID
  */
u16 LCD_Read_ID(void)
{
    u8 val[4] = {0};
    LCD_ReadReg(0xD3, val, 4);
    return (val[2] << 8) | val[3];
}

/**
  * @brief  Lcd reset
  * @retval None
  */
void LCD_RESET(void)
{
    LCD_RST_CLR;
    Sys_Delay_ms(50);
    LCD_RST_SET;
    Sys_Delay_ms(50);
}

/**
  * @brief  Lcd clear
  * @retval None
  */
void LCD_Clear(u16 Color)
{
    unsigned int i;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    for (i = 0; i < lcddev.height * lcddev.width; i++)
    {
        Lcd_WriteData_16Bit(Color);
    }
}

/**
  * @brief  Lcd direction set
  * @retval None
  */
void LCD_direction(u8 direction)
{
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    lcddev.rramcmd = 0x2E;
    switch (direction)
    {
    case 0:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        LCD_WriteReg(0x36, (1 << 3));
        break;
    case 1:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 5) | (1 << 6));
        break;
    case 2:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 4) | (1 << 6));
        break;
    case 3:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 5) | (1 << 4));
        break;
    default:
        break;
    }
}

/**
  * @brief  Lcd windows size set
  * @retval None
  */
void LCD_SetWindows(u16 xStar, u16 yStar, u16 xEnd, u16 yEnd)
{
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(xStar >> 8);
    LCD_WR_DATA(0x00FF & xStar);
    LCD_WR_DATA(xEnd >> 8);
    LCD_WR_DATA(0x00FF & xEnd);

    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(yStar >> 8);
    LCD_WR_DATA(0x00FF & yStar);
    LCD_WR_DATA(yEnd >> 8);
    LCD_WR_DATA(0x00FF & yEnd);

    LCD_WriteRAM_Prepare();
}

/**
  * @brief  Lcd cursor set
  * @retval None
  */
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

/**
  * @brief  Set designated spot color
  * @retval None
  */
void LCD_DrawPoint(u16 x, u16 y,u16 point_color)
{
    LCD_SetCursor(x, y);
    Lcd_WriteData_16Bit(point_color);
}

/**
  * @brief  Get designated spot color
  * @retval color
  */
u16 LCD_ReadPoint(u16 x, u16 y)
{
    u16 color;
    if(x>=lcddev.width||y>=lcddev.height)
    {
        return 0;
    }
    LCD_SetCursor(x,y);
    LCD_ReadRAM_Prepare();
    GPIOB->CRL=0X88888888;
    GPIOB->CRH=0X88888888;
    GPIOB->ODR=0XFFFF;   
    color = Lcd_ReadData_16Bit();
    GPIOB->CRL=0X33333333; 	
    GPIOB->CRH=0X33333333; 		
    GPIOB->ODR=0XFFFF;    		
    return color;
}

/**
  * @brief  Draw line
  * @retval None
  */
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x2 - x1; 
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
        incx = 1;
    else if (delta_x == 0)
        incx = 0; 
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; 
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; 
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) 
    {
        LCD_DrawPoint(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
  * @brief  Draw rectangle
  * @retval None
  */
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}

/**
  * @brief  Fill rectangle
  * @retval None
  */
void LCD_FillRectangle(u16 sx, u16 sy, u16 ex, u16 ey,  u16 color, u8 mode)
{
    u16 i, j;    
    LCD_SetWindows(sx, sy, ex, ey);
    if (mode == FILL_MODE_UP)
    {
        for (i = sy; i < ey; i++)
        {
            for (j = sx; j < ex; j++)
                LCD_DrawPoint(j, i, color);
        }
    }
    else
    {
        for (i = sx; i < ex; i++)
        {
            for (j = sy; j < ey; j++)
                LCD_DrawPoint(i, j, WHITE);
            Sys_Delay_ms(1);
        }
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1); 
}

/**
  * @brief  Draw circle
  * @retval None
  */
void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
{
    LCD_DrawPoint(xc + x, yc + y, c);

    LCD_DrawPoint(xc - x, yc + y, c);

    LCD_DrawPoint(xc + x, yc - y, c);

    LCD_DrawPoint(xc - x, yc - y, c);

    LCD_DrawPoint(xc + y, yc + x, c);

    LCD_DrawPoint(xc - y, yc + x, c);

    LCD_DrawPoint(xc + y, yc - x, c);

    LCD_DrawPoint(xc - y, yc - x, c);
}

/**
  * @brief  Draw circle (fill or no fill)
  * @retval None
  */
void gui_circle(int xc, int yc, u16 c, int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;

    if (fill)
    {
        while (x <= y)
        {
            for (yi = x; yi <= y; yi++)
                _draw_circle_8(xc, yc, x, yi, c);

            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    else
    {
        while (x <= y)
        {
            _draw_circle_8(xc, yc, x, y, c);
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

/**
  * @brief  Draw triangel
  * @retval None
  */
void Draw_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    LCD_DrawLine(x0, y0, x1, y1, color);
    LCD_DrawLine(x1, y1, x2, y2, color);
    LCD_DrawLine(x2, y2, x0, y0, color);
}

static void _swap(u16 *a, u16 *b)
{
    u16 tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
  * @brief  Fill triangel
  * @retval None
  */
void Fill_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0;
    long sb = 0;
    if (y0 > y1)
    {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y1 > y2)
    {
        _swap(&y2, &y1);
        _swap(&x2, &x1);
    }
    if (y0 > y1)
    {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y0 == y2)
    {
        a = b = x0;
        if (x1 < a)
        {
            a = x1;
        }
        else if (x1 > b)
        {
            b = x1;
        }
        if (x2 < a)
        {
            a = x2;
        }
        else if (x2 > b)
        {
            b = x2;
        }
        LCD_FillRectangle(a, y0, b, y0, POINT_COLOR, FILL_MODE_UP);
        return;
    }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if (y1 == y2)
    {
        last = y1;
    }
    else
    {
        last = y1 - 1;
    }
    for (y = y0; y <= last; y++)
    {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b)
        {
            _swap(&a, &b);
        }
        LCD_FillRectangle(a, y, b, y, POINT_COLOR, FILL_MODE_UP);
    }
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++)
    {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b)
        {
            _swap(&a, &b);
        }
        LCD_FillRectangle(a, y, b, y, POINT_COLOR, FILL_MODE_UP);
    }
}

/**
  * @brief  Displays char
  * @retval None
  */
void LCD_ShowChar(u16 x, u16 y, u16 fc, u16 bc, u8 num, u8 size, u8 mode)
{
    u8 temp;
    u8 pos, t;
    u16 colortemp = POINT_COLOR;
    num = num - ' ';                                      
    LCD_SetWindows(x, y, x + size / 2 - 1, y + size - 1);
    if (!mode)                                            
    {
        for (pos = 0; pos < size; pos++)
        {
            if (size == 12)
                temp = asc2_1206[num][pos]; 
            else
                temp = asc2_1608[num][pos]; 
            for (t = 0; t < size / 2; t++)
            {
                if (temp & 0x01)
                    Lcd_WriteData_16Bit(fc);
                else
                    Lcd_WriteData_16Bit(bc);
                temp >>= 1;
            }
        }
    }
    else 
    {
        for (pos = 0; pos < size; pos++)
        {
            if (size == 12)
                temp = asc2_1206[num][pos];
            else
                temp = asc2_1608[num][pos]; 
            for (t = 0; t < size / 2; t++)
            {
                POINT_COLOR = fc;
                if (temp & 0x01)
                    LCD_DrawPoint(x + t, y + pos, POINT_COLOR); 
                temp >>= 1;
            }
        }
    }
    POINT_COLOR = colortemp;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/**
  * @brief  Displays string
  * @retval None
  */
void LCD_ShowString(u16 x, u16 y, u8 size, u8 *p, u8 mode)
{
    while ((*p <= '~') && (*p >= ' ')) 
    {
        if (x > (lcddev.width - 1) || y > (lcddev.height - 1))
            return;
        LCD_ShowChar(x, y, POINT_COLOR, BACK_COLOR, *p, size, mode);
        x += size / 2;
        p++;
    }
}

/**
  * @brief  Get designated spot data
  * @retval None
  */
u32 mypow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
        result *= m;
    return result;
}

/**
  * @brief  Displays number
  * @retval None
  */
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size)
{
    u8 t, temp;
    u8 enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + (size / 2) * t, y, POINT_COLOR, BACK_COLOR, ' ', size, 0);
                continue;
            }
            else
                enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, POINT_COLOR, BACK_COLOR, temp + '0', size, 0);
    }
}

/**
  * @brief  Displays 16 * 16 chinese char
  * @retval None
  */
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode)
{
    u8 i, j;
    u16 k;
    u16 HZnum;
    u16 x0 = x;
    HZnum = sizeof(tfont16) / sizeof(typFNT_GB16);

    for (k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
            LCD_SetWindows(x, y, x + 16 - 1, y + 16 - 1);
            for (i = 0; i < 16 * 2; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) 
                    {
                        if (tfont16[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    }
                    else
                    {
                        POINT_COLOR = fc;
                        if (tfont16[k].Msk[i] & (0x80 >> j))
                            LCD_DrawPoint(x, y, POINT_COLOR);
                        x++;
                        if ((x - x0) == 16)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/**
  * @brief  Displays 24 * 24 chinese char
  * @retval None
  */
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode)
{
    u8 i, j;
    u16 k;
    u16 HZnum;
    u16 x0 = x;
    HZnum = sizeof(tfont24) / sizeof(typFNT_GB24);

    for (k = 0; k < HZnum; k++)
    {
        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
        {
            LCD_SetWindows(x, y, x + 24 - 1, y + 24 - 1);
            for (i = 0; i < 24 * 3; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont24[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    }
                    else
                    {
                        POINT_COLOR = fc;
                        if (tfont24[k].Msk[i] & (0x80 >> j))
                            LCD_DrawPoint(x, y, POINT_COLOR); 
                        x++;
                        if ((x - x0) == 24)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; 
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/**
  * @brief  Displays 32 * 32 chinese char
  * @retval None
  */
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode)
{
    u8 i, j;
    u16 k;
    u16 HZnum;
    u16 x0 = x;
    HZnum = sizeof(tfont32) / sizeof(typFNT_GB32);
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
        {
            LCD_SetWindows(x, y, x + 32 - 1, y + 32 - 1);
            for (i = 0; i < 32 * 4; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont32[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    }
                    else
                    {
                        POINT_COLOR = fc;
                        if (tfont32[k].Msk[i] & (0x80 >> j))
                            LCD_DrawPoint(x, y, POINT_COLOR);
                        x++;
                        if ((x - x0) == 32)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/**
  * @brief  Displays chinese and english string
  * @retval None
  */
void GUI_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode)
{
    u16 x0 = x;
    u8 bHz = 0;       
    while (*str != 0) 
    {
        if (!bHz)
        {
            if (x > (lcddev.width - size / 2) || y > (lcddev.height - size))
                return;
            if (*str > 0x80)
                bHz = 1; //chinese
            else         //char
            {
                if (*str == 0x0D)
                {
                    y += size;
                    x = x0;
                    str++;
                }
                else
                {
                    if (size > 16) 
                    {
                        LCD_ShowChar(x, y, fc, bc, *str, 16, mode);
                        x += 8; 
                    }
                    else
                    {
                        LCD_ShowChar(x, y, fc, bc, *str, size, mode);
                        x += size / 2; 
                    }
                }
                str++;
            }
        }
        else //chinese
        {
            if (x > (lcddev.width - size) || y > (lcddev.height - size))
                return;
            bHz = 0; 
            if (size == 32)
                GUI_DrawFont32(x, y, fc, bc, str, mode);
            else if (size == 24)
                GUI_DrawFont24(x, y, fc, bc, str, mode);
            else
                GUI_DrawFont16(x, y, fc, bc, str, mode);
            str += 2;
            x += size; 
        }
    }
}

/**
  * @brief  Displays english string center
  * @retval None
  */
void GUI_StrCenterEn(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode)
{
    u16 len = strlen((const char *)str);
    u16 x1 = (lcddev.width - len * size / 2) / 2;
    GUI_Str(x1, y, fc, bc, str, size, mode);
}

/**
  * @brief  Displays chinese string center
  * @retval None
  */
void GUI_StrCenterCh(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode)
{
    u16 len = strlen((const char *)str);
    u16 x1 = (lcddev.width - len / 2 * size) / 2;
    GUI_Str(x1, y, fc, bc, str, size, mode);
}

/**
  * @brief  Displays specified size image
  * @retval None
  */
void GUI_Drawbmp16(u16 x, u16 y, u16 width, u16 height, const unsigned char *p)
{
    int i;
    unsigned char picH, picL;
    LCD_SetWindows(x, y, x + width - 1, y + height - 1);
    for (i = 0; i < width * height; i++)
    {
        picL = *(p + i * 2);
        picH = *(p + i * 2 + 1);
        Lcd_WriteData_16Bit(picH << 8 | picL);
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1); 
}

/**
  * @brief  Startup gui
  * @retval None
  */
void Startup_Animation(void)
{    
     GUI_StrCenterEn(0, 220, WHITE, BLACK, "Copyright(C) 2020 TatBoy and IoneStu PanGu V1.5", 12, 0);
     LCD_DrawRectangle(0, 160, 320, 180, WHITE);
     LCD_FillRectangle(0, 160, 160, 180, POINT_COLOR, FILL_MODE_LEFT);
}
