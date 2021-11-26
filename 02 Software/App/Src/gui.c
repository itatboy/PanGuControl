/**
  ******************************************************************************
  * File Name          : fly.c
  * Description        : This file provides code for the configuration
  *                      of the gui instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "gui.h"
#include "stdio.h"
#include "menu.h"
#include "button.h"
#include "pic.h"
    
GUIINFO_T guiinfo;

MENU_T const Key_table[64] = {
    /* ��ǰ���ϣ��£�ȷ�������� */
    {0, 1, 1, 2, 0, (*MainInterface)},
    {1, 0, 0, 0, 0, (*BackInterface)},
    /* ͨ������ */
    {2, 10, 3, 0, 0, (*GeneralSet)},
    {3, 10, 4, 0, 0, (*GeneralSet_1)}, //����
    {4, 3, 5, 4, 0, (*GeneralSet_2)}, //У׼
    {5, 4, 6, 5, 0, (*GeneralSet_3)}, //����
    {6, 5, 7, 6, 0, (*GeneralSet_4)}, //ģ��
    {7, 6, 8, 7, 0, (*GeneralSet_5)}, //ң�ص��
    {8, 7, 9, 8, 0, (*GeneralSet_6)}, //ģ�͵��
    {9, 8, 10, 9, 0, (*GeneralSet_7)}, //ң�صͱ�
    {10, 9, 3, 10, 0, (*GeneralSet_8)}, //ģ�͵ͱ�
    
    /* ר������ */
    {3, 3, 3, 0, 0, (*ExpertsSet)}, 
    {3, 3, 4, 0, 0, (*ExpertsSet_1)}, 
    {4, 3, 5, 0, 0, (*ExpertsSet_2)}, 
    {5, 4, 6, 0, 0, (*ExpertsSet_3)}, 
    {6, 5, 7, 0, 0, (*ExpertsSet_4)}, 
    {7, 6, 7, 0, 0, (*ExpertsSet_5)}, 
};

/*
    ������
*/
void MainInterface(void)
{
    if(!pg.LockFlag)
    {
        GUI_Str(0, 2, guiinfo.usMainCol, BLACK,"������ģʽ��", 16, 0); 
    }
    else
    {
      GUI_Str(17, 2, guiinfo.usMainCol, BLACK,"����ģʽ", 16, 0); 
    }
  
    GUI_Str(15, 30, guiinfo.usMinorCol, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 55, guiinfo.usMinorCol, BLACK, "RSSI:", 16, 0);

    LCD_DrawRectangle(pg.usChLeftLowerX[THROTTLE], 114, 28, 216, guiinfo.usMainCol);
    GUI_Str(10, 219, guiinfo.usMainCol, BLACK, "Throt", 12, 0);

    LCD_DrawRectangle(pg.usChLeftLowerX[ROLL], 114, 58, 216, guiinfo.usMainCol);
    GUI_Str(44, 219, guiinfo.usMainCol, BLACK, "Roll", 12, 0);
    
    LCD_DrawRectangle(pg.usChLeftLowerX[YAW], 114, 270, 216, guiinfo.usMainCol);
    GUI_Str(258, 219, guiinfo.usMainCol, BLACK, "Yaw", 12, 0);

    LCD_DrawRectangle(pg.usChLeftLowerX[PITCH], 114, 300, 216, guiinfo.usMainCol);
    GUI_Str(284, 219, guiinfo.usMainCol, BLACK, "Pitch", 12, 0);
    
    if (gsSYSPARA.usModel == 0)
        GUI_Drawbmp16(128, 110, 64, 64, gImage_1);//��ģ
    else if (gsSYSPARA.usModel == 1)
        GUI_Drawbmp16(128, 110, 64, 64, gImage_2);//��ģ
    else 
        GUI_Drawbmp16(128, 110, 64, 64, gImage_3);//��ģ
}

/*
    �ش�����
*/
void BackInterface(void)
{
    GUI_Str(0, 2, WHITE, BLACK,"���ش���Ϣ��", 16, 0);
}

/*
    ר������
*/
void ExpertsSet(void)
{
    GUI_Str(0, 2, WHITE, BLACK,"���߼����á�", 16, 0);  
    GUI_Str(15, 30, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 60, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 90, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 120, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 150, YELLOW, BLACK, "MODE:", 16, 0);
}

void ExpertsSet_1(void)
{
    GUI_Str(15, 30, YELLOW, WHITE, "MODE:", 16, 0);
    GUI_Str(15, 60, YELLOW, BLACK, "MODE:", 16, 0);
}

void ExpertsSet_2(void)
{
    GUI_Str(15, 30, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 60, YELLOW, WHITE, "MODE:", 16, 1);
    GUI_Str(15, 90, YELLOW, BLACK, "MODE:", 16, 0);
}

void ExpertsSet_3(void)
{
    GUI_Str(15, 60, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 90, YELLOW, WHITE, "MODE:", 16, 1);
    GUI_Str(15, 120, YELLOW, BLACK, "MODE:", 16, 0);
}

void ExpertsSet_4(void)
{
    GUI_Str(15, 90, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 120, YELLOW, WHITE, "MODE:", 16, 0);
    GUI_Str(15, 150, YELLOW, BLACK, "MODE:", 16, 0);
}

void ExpertsSet_5(void)
{
    GUI_Str(15, 120, YELLOW, BLACK, "MODE:", 16, 0);
    GUI_Str(15, 150, YELLOW, WHITE, "MODE:", 16, 0);
}

/*
    ͨ������
*/
void GeneralSet(void)
{
    u8 temp[5];
    GUI_Str(0, 2, WHITE, BLACK,"��ͨ�����á�", 16, 0);
    
    /* ���� */
    GUI_Str(30, 50, guiinfo.usMinorCol, BLACK, "����: ", 16, 0);
    if (!guiinfo.ucLanguage)
        GUI_Str(78, 50, guiinfo.usMainCol, BLACK, "����", 16, 0);
    else
        GUI_Str(78, 50, guiinfo.usMainCol, BLACK, "English", 16, 0);
    
    /* У׼ */
    GUI_Str(190, 50, guiinfo.usMinorCol, BLACK, "У׼��", 16, 0);
    if (!gsSYSPARA.usCorrect)
        GUI_Str(238, 50, guiinfo.usMainCol, BLACK, "��", 16, 0);
    else
        GUI_Str(238, 50, guiinfo.usMainCol, BLACK, "��", 16, 0);
    
    /* ���� */
    GUI_Str(30, 80, guiinfo.usMinorCol, BLACK, "����: ", 16, 0);
    if (!gsSYSPARA.usVoice)
        GUI_Str(78, 80, guiinfo.usMainCol, BLACK, "��", 16, 0);
    else
        GUI_Str(78, 80, guiinfo.usMainCol, BLACK, "��", 16, 0);
    
    /* ģ�� */
    GUI_Str(190, 80, guiinfo.usMinorCol, BLACK, "ģ��: ", 16, 0);
    if (gsSYSPARA.usModel == 0)
      GUI_Str(238, 80, guiinfo.usMainCol, BLACK, "��ģ", 16, 0);
    else if (gsSYSPARA.usModel == 1)
      GUI_Str(238, 80, guiinfo.usMainCol, BLACK, "��ģ", 16, 0);
    else 
      GUI_Str(238, 80, guiinfo.usMainCol, BLACK, "��ģ", 16, 0);

    /* ң�ص������ */
    GUI_Str(30, 110, guiinfo.usMinorCol, BLACK, "ң�ص�أ�", 16, 0);
    if (gsSYSPARA.usMasterBatteryType == 0)
        GUI_Str(110, 110, guiinfo.usMainCol, BLACK, "1S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 1)
        GUI_Str(110, 110, guiinfo.usMainCol, BLACK, "2S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 2)
        GUI_Str(110, 110, guiinfo.usMainCol, BLACK, "3S", 16, 0);
    
    /* ģ�͵������ */
    GUI_Str(190, 110, guiinfo.usMinorCol, BLACK, "ģ�͵�أ�", 16, 0);
    if (gsSYSPARA.usSlaveBatteryType == 0)
        GUI_Str(270, 110, guiinfo.usMainCol, BLACK, "1S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 1)
        GUI_Str(270, 110, guiinfo.usMainCol, BLACK, "2S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 2)
        GUI_Str(270, 110, guiinfo.usMainCol, BLACK, "3S", 16, 0); 
    
    /* ң�ر�����ѹ */
    GUI_Str(30, 140, guiinfo.usMinorCol, BLACK, "ң�صͱ���", 16, 0); 
    sprintf((char *)temp, "%d", gsSYSPARA.fMasterBatteryProtect);
    GUI_Str(110, 140, guiinfo.usMainCol, BLACK, temp, 16, 0);
    
    /* ģ�ͱ�����ѹ */
    GUI_Str(190, 140, guiinfo.usMinorCol, BLACK, "ģ�͵ͱ���", 16, 0);
    sprintf((char *)temp, "%d", gsSYSPARA.fSlaveBatteryProtect);
    GUI_Str(270, 140, guiinfo.usMainCol, BLACK, temp, 16, 0);
}

/*
    ͨ������-����
*/
void GeneralSet_1(void)
{
    u8 temp[5];
    //���ϼ�����
    sprintf((char *)temp, "%d", gsSYSPARA.fSlaveBatteryProtect);
    GUI_Str(270, 140, WHITE, BLACK, temp, 16, 0);
    
    if (!guiinfo.ucLanguage)
        GUI_Str(78, 50, BLACK, WHITE, "����", 16, 0);
    else
        GUI_Str(78, 50, BLACK, WHITE, "English", 16, 0);
    //���¼�����
    if (!gsSYSPARA.usCorrect)
        GUI_Str(238, 50, WHITE, BLACK, "��", 16, 0);
    else
        GUI_Str(238, 50, WHITE, BLACK, "��", 16, 0);
}

/*
    ͨ������-����
*/
void GeneralSet_2(void)
{
    //���ϼ�����
    if (!guiinfo.ucLanguage)
        GUI_Str(78, 50, WHITE, BLACK, "����", 16, 0);
    else
        GUI_Str(78, 50, WHITE, BLACK, "English", 16, 0);
  
    if (!gsSYSPARA.usCorrect)
        GUI_Str(238, 50, BLACK, WHITE, "��", 16, 0);
    else
        GUI_Str(238, 50, BLACK, WHITE, "��", 16, 0);
    //���¼�����
    if (!gsSYSPARA.usVoice)
        GUI_Str(78, 80, WHITE, BLACK, "��", 16, 0);
    else
        GUI_Str(78, 80, WHITE, BLACK, "��", 16, 0);
}

/*
    ͨ������-����
*/
void GeneralSet_3(void)
{
    //���ϼ�����
    if (!gsSYSPARA.usCorrect)
        GUI_Str(238, 50, WHITE, BLACK, "��", 16, 0);
    else
        GUI_Str(238, 50, WHITE, BLACK, "��", 16, 0);
  
    if (!gsSYSPARA.usVoice)
        GUI_Str(78, 80, BLACK, WHITE, "��", 16, 0);
    else
        GUI_Str(78, 80, BLACK, WHITE, "��", 16, 0);
    //���¼�����
    if (gsSYSPARA.usModel == 0)
      GUI_Str(238, 80, WHITE, BLACK, "��ģ", 16, 0);
    else if (gsSYSPARA.usModel == 1)
      GUI_Str(238, 80, WHITE, BLACK, "��ģ", 16, 0);
    else 
      GUI_Str(238, 80, WHITE, BLACK, "��ģ", 16, 0);
}

/*
    ͨ������-ģ��
*/
void GeneralSet_4(void)
{
    //���ϼ�����
    if (!gsSYSPARA.usVoice)
        GUI_Str(78, 80, WHITE, BLACK, "��", 16, 0);
    else
        GUI_Str(78, 80, WHITE, BLACK, "��", 16, 0);
  
    if (gsSYSPARA.usModel == 0)
      GUI_Str(238, 80, BLACK, WHITE, "��ģ", 16, 0);
    else if (gsSYSPARA.usModel == 1)
      GUI_Str(238, 80, BLACK, WHITE, "��ģ", 16, 0);
    else 
      GUI_Str(238, 80, BLACK, WHITE, "��ģ", 16, 0);
    //���¼�����
    if (gsSYSPARA.usMasterBatteryType == 0)
        GUI_Str(110, 110, WHITE, BLACK, "1S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 1)
        GUI_Str(110, 110, WHITE, BLACK, "2S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 2)
        GUI_Str(110, 110, WHITE, BLACK, "3S", 16, 0);
}

/*
    ͨ������-ң�ص��
*/
void GeneralSet_5(void)
{
    //���ϼ�����
    if (gsSYSPARA.usModel == 0)
      GUI_Str(238, 80, WHITE, BLACK, "��ģ", 16, 0);
    else if (gsSYSPARA.usModel == 1)
      GUI_Str(238, 80, WHITE, BLACK, "��ģ", 16, 0);
    else 
      GUI_Str(238, 80, WHITE, BLACK, "��ģ", 16, 0);
  
    if (gsSYSPARA.usMasterBatteryType == 0)
        GUI_Str(110, 110, BLACK, WHITE, "1S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 1)
        GUI_Str(110, 110, BLACK, WHITE, "2S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 2)
        GUI_Str(110, 110, BLACK, WHITE, "3S", 16, 0);
    //���¼�����
    if (gsSYSPARA.usSlaveBatteryType == 0)
        GUI_Str(270, 110, WHITE, BLACK, "1S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 1)
        GUI_Str(270, 110, WHITE, BLACK, "2S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 2)
        GUI_Str(270, 110, WHITE, BLACK, "3S", 16, 0);
}

/*
    ͨ������-ģ�͵��
*/
void GeneralSet_6(void)
{
    u8 temp[5];
    //���ϼ�����
    if (gsSYSPARA.usMasterBatteryType == 0)
        GUI_Str(110, 110, WHITE, BLACK, "1S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 1)
        GUI_Str(110, 110, WHITE, BLACK, "2S", 16, 0);
    else if (gsSYSPARA.usMasterBatteryType == 2)
        GUI_Str(110, 110, WHITE, BLACK, "3S", 16, 0);
  
    if (gsSYSPARA.usSlaveBatteryType == 0)
        GUI_Str(270, 110, BLACK, WHITE, "1S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 1)
        GUI_Str(270, 110, BLACK, WHITE, "2S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 2)
        GUI_Str(270, 110, BLACK, WHITE, "3S", 16, 0);
    //���¼�����
    sprintf((char *)temp, "%d", gsSYSPARA.fMasterBatteryProtect);
    GUI_Str(110, 140, WHITE, BLACK, temp, 16, 0);
}

/*
    ͨ������-ң�صͱ�
*/
void GeneralSet_7(void)
{
    u8 temp[5];
    //���ϼ�����
    if (gsSYSPARA.usSlaveBatteryType == 0)
        GUI_Str(270, 110, WHITE, BLACK, "1S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 1)
        GUI_Str(270, 110, WHITE, BLACK, "2S", 16, 0);
    else if (gsSYSPARA.usSlaveBatteryType == 2)
        GUI_Str(270, 110, WHITE, BLACK, "3S", 16, 0);
    
    sprintf((char *)temp, "%d", gsSYSPARA.fMasterBatteryProtect);
    GUI_Str(110, 140, BLACK, WHITE, temp, 16, 0);
    //���¼�����
    sprintf((char *)temp, "%d", gsSYSPARA.fSlaveBatteryProtect);
    GUI_Str(270, 140, WHITE, BLACK, temp, 16, 0);
}

/*
    ͨ������-ģ�͵ͱ�
*/
void GeneralSet_8(void)
{
    u8 temp[5];
    //���ϼ�����
    sprintf((char *)temp, "%d", gsSYSPARA.fMasterBatteryProtect);
    GUI_Str(110, 140, WHITE, BLACK, temp, 16, 0);
    
    sprintf((char *)temp, "%d", gsSYSPARA.fSlaveBatteryProtect);
    GUI_Str(270, 140, BLACK, WHITE, temp, 16, 0);
    //���¼�����
    if (!guiinfo.ucLanguage)
        GUI_Str(78, 50, WHITE, BLACK, "����", 16, 0);
    else
        GUI_Str(78, 50, WHITE, BLACK, "English", 16, 0);
}

void Color_Set(u16 usBackdropCol, u16 usMainCol, u16 usMinorCol)
{
    guiinfo.usMainCol = usMainCol;
    guiinfo.usMinorCol = usMinorCol;
}

void button_up_callback(void *button)
{
    uint32_t btn_event_val; 
      btn_event_val = get_button_event((struct Button *)button); 
    
      switch(btn_event_val)
      {
	    case PRESS_DOWN:
	    	break; 
	    case PRESS_UP: 
                guiinfo.ucNowIndex = Key_table[guiinfo.ucNowIndex].up;
	    	break;  
	    case PRESS_REPEAT: 
	    	break; 
	    case SINGLE_CLICK: 
	    	break;          
	    case DOUBLE_CLICK: 
	    	break;     
	    case LONG_PRESS_START:
	   	break; 
	    case LONG_PRESS_HOLD: 
	    	break; 
	}
      Buzzer(1);
      Key_table[guiinfo.ucNowIndex].function();
}

void button_down_callback(void *button)
{
    uint32_t btn_event_val; 
      btn_event_val = get_button_event((struct Button *)button); 
    
      switch(btn_event_val)
      {
	    case PRESS_DOWN:
	    	break; 
	    case PRESS_UP: 
                guiinfo.ucNowIndex = Key_table[guiinfo.ucNowIndex].down;
	    	break;  
	    case PRESS_REPEAT: 
	    	break; 
	    case SINGLE_CLICK:
	    	break;          
	    case DOUBLE_CLICK: 
	    	break;     
	    case LONG_PRESS_START:
	   	break; 
	    case LONG_PRESS_HOLD: 
	    	break; 
	}
      Buzzer(1);
      Key_table[guiinfo.ucNowIndex].function();
}

void button_enter_callback(void *button)
{
    uint32_t btn_event_val; 
      btn_event_val = get_button_event((struct Button *)button); 
    
      switch(btn_event_val)
      {
	    case PRESS_DOWN:
	    	break; 
	    case PRESS_UP: 
	    	break;  
	    case PRESS_REPEAT: 
	    	break; 
	    case SINGLE_CLICK:
                if (guiinfo.ucNowIndex == 4) //У׼
                {
                    gsSYSPARA.usCorrect = !gsSYSPARA.usCorrect;
                    if (gsSYSPARA.usCorrect)
                    {
                        Para_Reset();
                        Para_Map_FromEeprom();
                    }
                }
                else if (guiinfo.ucNowIndex == 5) //����
                    gsSYSPARA.usVoice = !gsSYSPARA.usVoice;
                else if (guiinfo.ucNowIndex == 6) //ģ��
                {
                    if (gsSYSPARA.usModel >= 2)
                        gsSYSPARA.usModel = 0;
                    else
                        gsSYSPARA.usModel++;
                }
                else if (guiinfo.ucNowIndex == 7) //ң�ص��
                {
                    if (gsSYSPARA.usMasterBatteryType >= 2)
                        gsSYSPARA.usMasterBatteryType = 0;
                    else
                        gsSYSPARA.usMasterBatteryType++;
                }
                else if (guiinfo.ucNowIndex == 8) //ģ�͵��
                {
                    if (gsSYSPARA.usSlaveBatteryType >= 2)
                        gsSYSPARA.usSlaveBatteryType = 0;
                    else
                        gsSYSPARA.usSlaveBatteryType++;
                }
                else if (guiinfo.ucNowIndex == 9) //ң�صͱ�
                {
                    if (gsSYSPARA.fMasterBatteryProtect >= 9)
                        gsSYSPARA.fMasterBatteryProtect = 0;
                    else
                        gsSYSPARA.fMasterBatteryProtect++;
                }
                else if (guiinfo.ucNowIndex == 10) //ģ�͵ͱ�
                {
                    if (gsSYSPARA.fSlaveBatteryProtect >= 9)
                        gsSYSPARA.fSlaveBatteryProtect = 0;
                    else
                        gsSYSPARA.fSlaveBatteryProtect++;
                }
                else
                  return;
	    	break;          
	    case DOUBLE_CLICK: 
                if ((guiinfo.ucNowIndex == 0) || (guiinfo.ucNowIndex == 1)) //����ͨ������ǰ���������
                {
                    Color_Set(0x00, BLACK, BLACK);
                    MainInterface();
                    for (u8 j = 0; j < CH_NUM; j++)
                      GUI_Str(pg.usChValeX[j], 98, BLACK, BLACK, "0000", 12, 0);
                    GUI_Str(128, 110, BLACK, BLACK, "        ", 16, 0);
                    GUI_Str(144, 110, BLACK, BLACK, "        ", 16, 0);
                    GUI_Str(160, 110, BLACK, BLACK, "        ", 16, 0);
                    GUI_Str(176, 110, BLACK, BLACK, "        ", 16, 0);
                    Color_Set(0x00, WHITE, YELLOW);
                }
                guiinfo.ucNowIndex = Key_table[guiinfo.ucNowIndex].enter;
	    	break;     
	    case LONG_PRESS_START:
	   	break; 
	    case LONG_PRESS_HOLD: 
	    	break; 
	}
      Buzzer(1);
      Key_table[guiinfo.ucNowIndex].function();
}

void button_back_callback(void *button)
{
    uint32_t btn_event_val; 
    btn_event_val = get_button_event((struct Button *)button); 
    
    switch(btn_event_val)
    {
        case PRESS_DOWN:
            break; 
        case PRESS_UP:
            if (guiinfo.ucNowIndex == 0)
                return;
            else if (2 <= guiinfo.ucNowIndex <= 10) //����������ǰ�����ʾ
            {
                gsSYSPARA.usCorrect = 0;
                Color_Set(0x00, BLACK, BLACK);
                GeneralSet();
                Color_Set(0x00, WHITE, BROWN);
                Para_Write(1, 1);
            }
            guiinfo.ucNowIndex = Key_table[guiinfo.ucNowIndex].back;
            break;  
        case PRESS_REPEAT:
            break; 
        case SINGLE_CLICK:
            break;          
        case DOUBLE_CLICK: 
            break;     
        case LONG_PRESS_START:
            break; 
        case LONG_PRESS_HOLD: 
            break; 
    }
    Buzzer(1);
    Key_table[guiinfo.ucNowIndex].function();
}
