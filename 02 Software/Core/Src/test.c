#include <stdio.h>
#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "pic.h"

u16 ColorTab[5] = {RED, GREEN, BLUE, YELLOW, BRED}; //������ɫ����
u16 ColornTab[8] = {RED, MAGENTA, GREEN, DARKBLUE, BLUE, BLACK, LIGHTGREEN};

void DrawTestPage(u8 *str)
{
    //���ƹ̶���up
    LCD_Clear(WHITE);
    LCD_Fill(0, 0, lcddev.width, 20, BLUE);
    //���ƹ̶���down
    LCD_Fill(0, lcddev.height - 20, lcddev.width, lcddev.height, BLUE);
    POINT_COLOR = WHITE;
    Gui_StrCenter(0, 2, WHITE, BLUE, str, 16, 1);                                       //������ʾ
    Gui_StrCenter(0, lcddev.height - 18, WHITE, BLUE, "http://www.lcdwiki.com", 16, 1); //������ʾ
    //���Ʋ�������
    //LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

void main_test(void)
{
    DrawTestPage("ȫ�������ۺϲ��Գ���");
    Gui_StrCenter(0, 30, RED, BLUE, "ȫ������", 16, 1);                     //������ʾ
    Gui_StrCenter(0, 60, RED, BLUE, "�ۺϲ��Գ���", 16, 1);                 //������ʾ
    Gui_StrCenter(0, 90, MAGENTA, BLUE, "2.4\" ILI9341 240X320", 16, 1);    //������ʾ
    Gui_StrCenter(0, 120, BLUE, BLUE, "xiaoFeng@QDtech 2018-11-13", 16, 1); //������ʾ
    Sys_Delay_ms(1500);
    Sys_Delay_ms(1500);
}

void Test_Color(void)
{
    //DrawTestPage("����1:��ɫ������");
    LCD_Fill(0, 0, lcddev.width, lcddev.height, WHITE);
    Show_Str(20, 30, BLUE, YELLOW, "BL Test", 16, 1);
    Sys_Delay_ms(800);
    LCD_Fill(0, 0, lcddev.width, lcddev.height, RED);
    Show_Str(20, 30, BLUE, YELLOW, "RED ", 16, 1);
    Sys_Delay_ms(800);
    LCD_Fill(0, 0, lcddev.width, lcddev.height, GREEN);
    Show_Str(20, 30, BLUE, YELLOW, "GREEN ", 16, 1);
    Sys_Delay_ms(800);
    LCD_Fill(0, 0, lcddev.width, lcddev.height, BLUE);
    Show_Str(20, 30, RED, YELLOW, "BLUE ", 16, 1);
    Sys_Delay_ms(800);
}

void Test_FillRec(void)
{
    u8 i = 0;
    DrawTestPage("����3:GUI����������");
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
    {
        POINT_COLOR = ColorTab[i];
        LCD_DrawRectangle(lcddev.width / 2 - 80 + (i * 15), lcddev.height / 2 - 80 + (i * 15), lcddev.width / 2 - 80 + (i * 15) + 60, lcddev.height / 2 - 80 + (i * 15) + 60);
    }
    Sys_Delay_ms(1500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
    {
        POINT_COLOR = ColorTab[i];
        LCD_DrawFillRectangle(lcddev.width / 2 - 80 + (i * 15), lcddev.height / 2 - 80 + (i * 15), lcddev.width / 2 - 80 + (i * 15) + 60, lcddev.height / 2 - 80 + (i * 15) + 60);
    }
    Sys_Delay_ms(1500);
}

void Test_Circle(void)
{
    u8 i = 0;
    DrawTestPage("����4:GUI��Բ������");
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
        gui_circle(lcddev.width / 2 - 80 + (i * 25), lcddev.height / 2 - 50 + (i * 25), ColorTab[i], 30, 0);
    Sys_Delay_ms(1500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
        gui_circle(lcddev.width / 2 - 80 + (i * 25), lcddev.height / 2 - 50 + (i * 25), ColorTab[i], 30, 1);
    Sys_Delay_ms(1500);
}

void English_Font_test(void)
{
    DrawTestPage("����6:Ӣ����ʾ����");
    Show_Str(10, 30, BLUE, YELLOW, "6X12:abcdefghijklmnopqrstuvwxyz0123456789", 12, 0);
    Show_Str(10, 45, BLUE, YELLOW, "6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12, 1);
    Show_Str(10, 60, BLUE, YELLOW, "6X12:~!@#$%^&*()_+{}:<>?/|-+.", 12, 0);
    Show_Str(10, 80, BLUE, YELLOW, "8X16:abcdefghijklmnopqrstuvwxyz0123456789", 16, 0);
    Show_Str(10, 100, BLUE, YELLOW, "8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 16, 1);
    Show_Str(10, 120, BLUE, YELLOW, "8X16:~!@#$%^&*()_+{}:<>?/|-+.", 16, 0);
    Sys_Delay_ms(1200);
}

void Test_Triangle(void)
{
    u8 i = 0;
    DrawTestPage("����5:GUI Triangle������");
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
    {
        POINT_COLOR = ColorTab[i];
        Draw_Triangel(lcddev.width / 2 - 80 + (i * 20), lcddev.height / 2 - 20 + (i * 15), lcddev.width / 2 - 50 - 1 + (i * 20), lcddev.height / 2 - 20 - 52 - 1 + (i * 15), lcddev.width / 2 - 20 - 1 + (i * 20), lcddev.height / 2 - 20 + (i * 15));
    }
    Sys_Delay_ms(1500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
    {
        POINT_COLOR = ColorTab[i];
        Fill_Triangel(lcddev.width / 2 - 80 + (i * 20), lcddev.height / 2 - 20 + (i * 15), lcddev.width / 2 - 50 - 1 + (i * 20), lcddev.height / 2 - 20 - 52 - 1 + (i * 15), lcddev.width / 2 - 20 - 1 + (i * 20), lcddev.height / 2 - 20 + (i * 15));
    }
    Sys_Delay_ms(1500);
}

void Chinese_Font_test(void)
{
    DrawTestPage("����7:������ʾ����");
    Show_Str(10, 30, BLUE, YELLOW, "16X16:ȫ�����Ӽ������޹�˾��ӭ��", 16, 0);
    Show_Str(10, 50, BLUE, YELLOW, "16X16:Welcomeȫ������", 16, 0);
    Show_Str(10, 70, BLUE, YELLOW, "24X24:���������Ĳ���", 24, 1);
    Show_Str(10, 100, BLUE, YELLOW, "32X32:�������", 32, 1);
    Sys_Delay_ms(1200);
}

void Pic_test(void)
{
    DrawTestPage("����8:ͼƬ��ʾ����");
    //LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    Gui_Drawbmp16(30, 30, gImage_qq);
    Show_Str(30 + 12, 75, BLUE, YELLOW, "QQ", 16, 1);
    Gui_Drawbmp16(90, 30, gImage_qq);
    Show_Str(90 + 12, 75, BLUE, YELLOW, "QQ", 16, 1);
    Gui_Drawbmp16(150, 30, gImage_qq);
    Show_Str(150 + 12, 75, BLUE, YELLOW, "QQ", 16, 1);
    Sys_Delay_ms(1200);
}

void Rotate_Test(void)
{
    u8 i = 0;
    u8 *Direction[4] = {"Rotation:0", "Rotation:90", "Rotation:180", "Rotation:270"};

    for (i = 0; i < 4; i++)
    {
        LCD_direction(i);
        DrawTestPage("����9:��Ļ��ת����");
        Show_Str(20, 30, BLUE, YELLOW, Direction[i], 16, 1);
        Gui_Drawbmp16(30, 50, gImage_qq);
        Sys_Delay_ms(1000);
        Sys_Delay_ms(1000);
    }
    LCD_direction(USE_HORIZONTAL);
}
