/**
  ******************************************************************************
  * File Name          : menu.c
  * Description        : This file provides code for the configuration
  *                      of the menu instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "menu.h"
#include "stdio.h"
#include "math.h"
#include "gui.h"
#include "button.h"

_PG_T pg = {
    .ChLower[0] = 600,
    .ChLower[1] = 600,
    .ChLower[2] = 600,
    .ChLower[3] = 600,
    /* ������ʾֵ������ */
    .usChValeX[THROTTLE] = 13,
    .usChValeX[ROLL] = 42,
    .usChValeX[YAW] = 254,
    .usChValeX[PITCH] = 284,
    /* ������ʾ�������½Ǻ����� */
    .usChLeftLowerX[THROTTLE] = 20,
    .usChLeftLowerX[ROLL] = 50,
    .usChLeftLowerX[YAW] = 262,
    .usChLeftLowerX[PITCH] = 292,
};
_SYSPARA_T gsSYSPARA;

/**
  * @brief  ������
  */
u8 BuzzerCount;
void Buzzer(u8 count)
{
    if (!gsSYSPARA.usVoice)
        BuzzerCount = count;
}
void Basic_Buzzer(void)
{
    static u8 flag;
    static u32 now, time;
    if (BuzzerCount == 0)
        return;
    if (TIME_AFTER(Sys_TickGetCount(), now, time))
    {
        now = Sys_TickGetCount();
        flag = !flag;
        if (flag)
        {
            Sys_Pin_Ctrl(BUZZER, ON, 0);
            time = ONTIME;
        }
        else
        {
            Sys_Pin_Ctrl(BUZZER, OFF, 0);
            time = OFFTIME;
            BuzzerCount--;
        }
    }
}

/**
  * @brief  ��������
  */
void Basic_SaveData(void)
{
    _SYSPARA_T tempPARA;
    u16 *src, *dst, bcc;

    if (!TIME_AFTER(Sys_TickGetCount(), pg.ulWriteTick, 3000)) //3���ִ���������
        return;
    pg.ulWriteTick = Sys_TickGetCount();

    if (!pg.ucWriteFlag) //д���ݱ�־Ϊ0ʱ��return
        return;
    pg.ucWriteFlag = 0;

    Sys_EEPROM_RdBytes(0, (u8 *)&tempPARA, sizeof(_SYSPARA_T));
    dst = (u16 *)&tempPARA;
    src = (u16 *)&gsSYSPARA;
    bcc = 0;
    for (u8 i = 1; i < sizeof(_SYSPARA_T) / sizeof(u16); i++)
    {
        bcc ^= src[i];
        if (src[i] != dst[i])
        {
            Sys_EEPROM_WrBytes(0 + i * 2, (u8 *)(src + i), sizeof(u16));
        }
    }
    if (bcc != tempPARA.usBccCheck)
    {
        gsSYSPARA.usBccCheck = bcc;
        Sys_EEPROM_WrBytes(0, (u8 *)&gsSYSPARA.usBccCheck, sizeof(u16));
    }
}

/**
  * @brief  ������ʾ
  */
void Basic_UiDisplay(void)
{
    static u32 now;
    static u16 LastVale[4];
    static u8 high, temp[5];
    if (TIME_AFTER(Sys_TickGetCount(), now, 200))
    {
        now = Sys_TickGetCount();
        if (guiinfo.ucNowIndex == MAIN_PAGE)
        {
            for (u8 j = 0; j < CH_NUM; j++)
            {
               if (fabs(pg.ChVale[j] - LastVale[j]) > 1)
               {
                /* ������ʾֵ */
                sprintf((char *)temp, "%d", pg.ChVale[j]);
                GUI_Str(pg.usChValeX[j], 98, BROWN, BLACK, temp, 12, 0);
                /* ������ʾ���� */
                high = ((pg.ChVale[j] - 1000) / 10);
                if (high >= 100)
                  high = 100;
                LCD_FillRectangle(pg.usChLeftLowerX[j]+2, 215 - high, pg.usChLeftLowerX[j] + 7, 215, BROWN, FILL_MODE_UP);
                LCD_FillRectangle(pg.usChLeftLowerX[j]+2, 115, pg.usChLeftLowerX[j] + 7, 215 - high, BLACK, FILL_MODE_UP);
                LastVale[j] = pg.ChVale[j];
                LCD_DrawLine(0, 0, 120, 0, BLACK);
                LCD_DrawLine(0, 115, 0, 215, BLACK);
               }
            }
        }
        else if (guiinfo.ucNowIndex == PASSBACK_PAGE)
        {
            ;
        }
    }
}

/**
  * @brief  ��������
  */
void Basic_Lock(void)
{
    static u8 lock;
    static u32 now;
    if ((guiinfo.ucNowIndex == MAIN_PAGE) || (guiinfo.ucNowIndex == PASSBACK_PAGE))
    {
        if (!pg.LockFlag)
        {
            if ((Sys_Adc_Get(ROLL) > 3000) && (Sys_Adc_Get(YAW) < 800) && !lock)
            {
                lock = 1;
                now = Sys_TickGetCount();
            }
            else if ((Sys_Adc_Get(ROLL) < 3000) || (Sys_Adc_Get(YAW) > 800))
                lock = 0;

            if ((TIME_AFTER(Sys_TickGetCount(), now, 2500)) && lock)
            {
                Buzzer(2);
                pg.LockFlag = 1;
                lock = 0;
                pg.ulUnLockTick = Sys_TickGetCount();
                GUI_Str(17, 2, WHITE, BLACK, "����ģʽ", 16, 0);
            }
        }
        else
        {
            if ((Sys_Adc_Get(ROLL) > 3000) && (Sys_Adc_Get(YAW) < 800) && !lock)
            {
                lock = 1;
                now = Sys_TickGetCount();
            }
            else if ((Sys_Adc_Get(ROLL) < 3000) || (Sys_Adc_Get(YAW) > 800))
                lock = 0;

            if ((TIME_AFTER(Sys_TickGetCount(), now, 1500)) && lock)
            {
                Buzzer(1);
                pg.LockFlag = 0;
                lock = 0;
                pg.ulUnLockTick = 0;
                GUI_Str(132, 2, WHITE, BLACK, "        ", 16, 0);
                GUI_Str(0, 2, WHITE, BLACK, "������ģʽ��", 16, 0);
            }
        }
    }
}

/**
  * @brief  ����ӳ��
  */
int mapChValue(int val, int lower, int middle, int upper, int reverse)
{
    if (val > upper)
        val = upper;
    if (val < lower)
        val = lower;
    if (val < middle)
    {
        val = ((val - lower) * (1500 - 1000) / (middle - lower) + 1000);
    }
    else
    {
        val = ((val - middle) * (2000 - 1500) / (upper - middle) + 1500);
    }
    return (reverse ? 3000 - val : val);
}

/**
  * @brief  Fly control
  */
void Basic_Link(void)
{
    int ret;
    static u8 step, j;
    for (j = 0; j < 4; j++)
        pg.ChTemp[j] = Sys_Adc_Get(j);
    for (j = 0; j < CH_NUM; j++)
    {
        pg.ChVale[j] = pg.ChAdjust[j] + mapChValue(pg.ChTemp[j],
                                                   pg.ChLower[j],
                                                   pg.ChMiddle[j],
                                                   pg.ChUpper[j],
                                                   0);
    }
    
    /* ��������£��������� */
    if (pg.LockFlag)
    {
        ret = Link_SendData(FUNCTION_CONTROL, pg.ChVale);
        if (ret)
          Buzzer(1); //���յ�ACK���ݣ�����
    }

    /* У׼ģʽ */
    if (gsSYSPARA.usCorrect)
    {
        switch (step)
        {
        case 0:
            for (j = 0; j < 4; j++)
            {
                pg.ChMiddle[j] = Sys_Adc_Get(j);
            }
            step = 1;
            break;
        case 1:
            for (j = 0; j < 4; j++)
            {
                pg.ChUpper[j] = MAX(pg.ChUpper[j], Sys_Adc_Get(j));
                pg.ChLower[j] = MIN(pg.ChLower[j], Sys_Adc_Get(j));
            }
            break;
        }
    }
    else if (step)
    {
        Para_Map_ToEeprom();
        step = 0;
    }
}

u8 cal_crc_table(u8 *ptr, u8 len) 
{
    unsigned char  crc = 0x00;

    while (len--)
    {
        crc = CRC8_table[crc ^ *ptr++];
    }
    return crc;
}

int Link_SendData(u8 ucFunction, u16 *pSendBuf)
{
    u8 buf[12], i;
    int ret = 0;
    buf[0] = 0x5A;
    switch (ucFunction)
    {
        case FUNCTION_CONTROL:
            buf[1] = FUNCTION_CONTROL;
            for (i = 1; i <= 4; i++)
            {
                buf[2*i] = (u8)(pSendBuf[i-1]>>8)&0xFF; //��8λ
                buf[2*i+1] = (u8)pSendBuf[i-1]&0xFF; //��8λ
            }
            break;
        case FUNCTION_SET:
            buf[1] = FUNCTION_SET;
            for (i = 1; i <= 9; i++)
                buf[i] = (u8)pSendBuf[i-1]&0xFF; //��8λ
            break;
    }
    buf[10] = cal_crc_table(buf, 10);
    ret = NRF24L01_TxPacket(buf, sizeof(buf));
    if (ret == 0x60)
        return 1;
    return 0;
}

/**
  * @brief  ��Դ����
  */
void Manage_Power(void)
{
    static float temp, lasttemp, median;
    static u8 voltage[5], width;
    temp = (float)Sys_Adc_Get(VOLTAGE) * (3.3 / 4096);
    temp = temp * (10 + 5) / 5;
    if (fabs(temp - lasttemp) >= 0.1)
    {
        lasttemp = temp;
        sprintf((char *)voltage, "%5.2fV", temp);
        GUI_Str(240, 2, WHITE, BLACK, voltage, 16, 0);
        median = (POWERVOLTAGE - gsSYSPARA.fMasterBatteryProtect) / 25;
        width = (u8)((temp - gsSYSPARA.fMasterBatteryProtect) / median);
        if (width <= 25)
        {
            LCD_FillRectangle(292, 6, (292 + width), 15, GREEN, FILL_MODE_UP);
            LCD_FillRectangle((292 + width + 1), 6, 317, 15, BLACK, FILL_MODE_UP);
        }
    }
    if (temp < gsSYSPARA.fMasterBatteryProtect)
    {
        Buzzer(1);
        GUI_StrCenterCh(0, 100, WHITE, BLACK, "ң�ص������㣬����������", 16, 1);
    }
}

/**
  * @brief  ����״̬����
  */
void Manage_Run(void)
{
    static u32 temp, second, minute;
    static u8 flag, time[5];
    if (!pg.LockFlag)
    {
        flag = !flag;
        if (flag)
            GUI_Str(152, 2, WHITE, BLACK, "��", 16, 0);
        else
            GUI_Str(152, 2, BLACK, BLACK, "��", 16, 0);
    }
    else
    {
        temp = (int)(Sys_TickGetCount() - pg.ulUnLockTick) / 1000;
        second = (int)temp % 60;
        minute = (int)temp / 60;
        sprintf((char *)time, "%02d : %02d", minute, second);
        GUI_StrCenterEn(0, 0, RED, BLACK, time, 16, 0);
    }
}

/**
  * @brief  ͨ�����ݴ洢
  */
void Para_Map_ToEeprom(void)
{
    gsSYSPARA.ChLower_0 = pg.ChLower[0];
    gsSYSPARA.ChLower_1 = pg.ChLower[1];
    gsSYSPARA.ChLower_2 = pg.ChLower[2];
    gsSYSPARA.ChLower_3 = pg.ChLower[3];
    
    gsSYSPARA.ChMiddle_0 = pg.ChMiddle[0];
    gsSYSPARA.ChMiddle_1 = pg.ChMiddle[1];
    gsSYSPARA.ChMiddle_2 = pg.ChMiddle[2];
    gsSYSPARA.ChMiddle_3 = pg.ChMiddle[3];

    gsSYSPARA.ChUpper_0 = pg.ChUpper[0];
    gsSYSPARA.ChUpper_1 = pg.ChUpper[1];
    gsSYSPARA.ChUpper_2 = pg.ChUpper[2];
    gsSYSPARA.ChUpper_3 = pg.ChUpper[3];
}

/**
  * @brief  ͨ�����ݶ�ȡ
  */
void Para_Map_FromEeprom(void)
{
    pg.ChLower[0] = gsSYSPARA.ChLower_0;
    pg.ChLower[1] = gsSYSPARA.ChLower_1; 
    pg.ChLower[2] = gsSYSPARA.ChLower_2; 
    pg.ChLower[3] = gsSYSPARA.ChLower_3; 
                    
    pg.ChMiddle[0] = gsSYSPARA.ChMiddle_0;
    pg.ChMiddle[1] = gsSYSPARA.ChMiddle_1;
    pg.ChMiddle[2] = gsSYSPARA.ChMiddle_2;
    pg.ChMiddle[3] = gsSYSPARA.ChMiddle_3;
                    
    pg.ChUpper[0] = gsSYSPARA.ChUpper_0; 
    pg.ChUpper[1] = gsSYSPARA.ChUpper_1; 
    pg.ChUpper[2] = gsSYSPARA.ChUpper_2; 
    pg.ChUpper[3] = gsSYSPARA.ChUpper_3; 
}

/**
  * @brief  ����д��
  */
void Para_Write(u8 writeflag, u8 writetick)
{
    if (writeflag < 2)
        pg.ucWriteFlag = writeflag;
    if (writetick)
        pg.ulWriteTick = Sys_TickGetCount();
}

/**
  * @brief  ������λ
  */
void Para_Reset(void)
{
    gsSYSPARA.usInitFlag = PARA_INIT_FLAG;

    gsSYSPARA.ChLower_0 = 600;
    gsSYSPARA.ChLower_1 = 600;
    gsSYSPARA.ChLower_2 = 600;
    gsSYSPARA.ChLower_3 = 600;

    gsSYSPARA.ChMiddle_0 = 2000;
    gsSYSPARA.ChMiddle_1 = 2000;
    gsSYSPARA.ChMiddle_2 = 2000;
    gsSYSPARA.ChMiddle_3 = 2000;

    gsSYSPARA.ChUpper_0 = 3000;
    gsSYSPARA.ChUpper_1 = 3000;
    gsSYSPARA.ChUpper_2 = 3000;
    gsSYSPARA.ChUpper_3 = 3000;
}

/**
  * @brief  ������ʼ��
  */
void Para_Init(void)
{
    u16 *tempbuf, bcc;
    u8 reset_para_flag = 0;
    Sys_EEPROM_RdBytes(0, (u8 *)&gsSYSPARA, sizeof(_SYSPARA_T));
    tempbuf = (u16 *)&gsSYSPARA;
    do
    {
        if (gsSYSPARA.usInitFlag != PARA_INIT_FLAG)
        {
            reset_para_flag = 1;
            break;
        }
        bcc = 0;
        for (u8 i = 1; i < sizeof(_SYSPARA_T) / sizeof(u16); i++)
        {
            bcc ^= tempbuf[i];
        }
        if (bcc != gsSYSPARA.usBccCheck)
        {
            reset_para_flag = 1;
            break;
        }

    } while (0);

    if (reset_para_flag)
    {
        memset((u8 *)&gsSYSPARA, 0, sizeof(_SYSPARA_T));
        Para_Reset();
        Para_Write(1, 1);
    }
    Para_Map_FromEeprom();
    return;
}

/**
  * @brief  Thread Basic
  */
void Thread_Basic(void)
{
    while (1)
    {
        Basic_Buzzer();
        Basic_SaveData();
        Basic_UiDisplay();
        Basic_Lock();
        Basic_Link();
        os_delayTick(2);
    }
}

/**
  * @brief  �����߳�
  */
void Thread_Button(void)
{
    while (1)
    {
        button_ticks();
        os_delayTick(5);
    }
}

/**
  * @brief  Thread Option
  */
void Thread_Option(void)
{
    while (1)
    {
        Manage_Power();
        Manage_Run();
        os_delayTick(500);
    }
}

struct Button button_up;
struct Button button_down;
struct Button button_enter;
struct Button button_back;
/**
  * @brief  Ӧ�ó�ʼ��
  */
void App_Init(void)
{
    button_init(&button_up, Sys_ReadPin_Up, 0);
    button_init(&button_down, Sys_ReadPin_Down, 0);
    button_init(&button_enter, Sys_ReadPin_Enter, 0);
    button_init(&button_back, Sys_ReadPin_Back, 0);

    button_attach(&button_up, PRESS_UP, button_up_callback);
    button_attach(&button_down, PRESS_UP, button_down_callback);
    button_attach(&button_enter, SINGLE_CLICK, button_enter_callback);
    button_attach(&button_enter, DOUBLE_CLICK, button_enter_callback);
    button_attach(&button_back, PRESS_UP, button_back_callback);

    button_start(&button_up);
    button_start(&button_down);
    button_start(&button_enter);
    button_start(&button_back);

    guiinfo.ucLanguage = 0;
    
    Color_Set(0x00, WHITE, YELLOW);
    /* Fill */
    GUI_Str(0, 160, BLACK, BLACK, "                                                        ", 16, 0);
    GUI_Str(0, 170, BLACK, BLACK, "                                                        ", 16, 0);
    GUI_StrCenterEn(0, 220, BLACK, BLACK, "Copyright(C) 2020 TatBoy and IoneStu PanGu V1.5", 12, 0);
    /* Draw */
    LCD_DrawRectangle(291, 5, 318, 15, WHITE);
    LCD_DrawLine(0, 20, 320, 20, RED);
    GUI_StrCenterEn(0, 220, WHITE, BLACK, "PanGu V1.5", 12, 0);

    Para_Init();
    MainInterface();
}

void Thread(void)
{
    App_Init();
    os_create((void *)Thread_Basic, 1, 300);
    os_create((void *)Thread_Button, 4, 200);
    os_create((void *)Thread_Option, 3, 300);
    os_start();
}
