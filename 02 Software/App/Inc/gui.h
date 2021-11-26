#ifndef __GUI_H__
#define __GUI_H__
#include "api.h"

typedef enum
{
    MAIN_PAGE = 0, //������
    PASSBACK_PAGE = 1, //�ش�����
    EXPERTS_PAGE = 2, //ר������
    GENERAL_PAGE = 30 //ͨ������
} PAGE;

/* �������ݽṹ */
typedef struct GUIINFO
{
    u8 ucNowIndex; //��ǰҳ��
  
    u8 ucLanguage; //���Ա�־λ

    u16 usMainCol; //��Ҫ��ɫ
    u16 usMinorCol; //��Ҫ��ɫ
    u16 usBackdropCol; //������ɫ
} GUIINFO_T;
extern GUIINFO_T guiinfo;

/* �˵����ݽṹ */
typedef struct
{
    u8 current;             //��ǰ������
    u8 up;                  //up������
    u8 down;                //down������
    u8 enter;               //enter������
    u8 back;                //back������
    void (*function)(void); //��ǰ�����Ŷ�Ӧ����
} MENU_T;

void MainInterface(void); //������
void BackInterface(void); //�ش�����
void CalibrationInterface(void); //У׼����

void ExpertsSet(void); //ר������
void ExpertsSet_1(void);
void ExpertsSet_2(void);
void ExpertsSet_3(void);
void ExpertsSet_4(void);
void ExpertsSet_5(void);

void GeneralSet(void); //ͨ������
void GeneralSet_1(void); //����
void GeneralSet_2(void); //����
void GeneralSet_3(void); //����
void GeneralSet_4(void); //ģ��
void GeneralSet_5(void); //ң�ص��
void GeneralSet_6(void); //ģ�͵��
void GeneralSet_7(void); //ң�صͱ�
void GeneralSet_8(void); //ģ�͵ͱ�

void Color_Set(u16 usBackdropCol, u16 usMainCol, u16 usMinorCol);
void button_up_callback(void *button);
void button_down_callback(void *button);
void button_enter_callback(void *button);
void button_back_callback(void *button);

#endif
