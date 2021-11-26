#ifndef __GUI_H__
#define __GUI_H__
#include "api.h"

typedef enum
{
    MAIN_PAGE = 0, //主界面
    PASSBACK_PAGE = 1, //回传界面
    EXPERTS_PAGE = 2, //专家设置
    GENERAL_PAGE = 30 //通用设置
} PAGE;

/* 设置数据结构 */
typedef struct GUIINFO
{
    u8 ucNowIndex; //当前页面
  
    u8 ucLanguage; //语言标志位

    u16 usMainCol; //主要颜色
    u16 usMinorCol; //次要颜色
    u16 usBackdropCol; //背景颜色
} GUIINFO_T;
extern GUIINFO_T guiinfo;

/* 菜单数据结构 */
typedef struct
{
    u8 current;             //当前索引号
    u8 up;                  //up索引号
    u8 down;                //down索引号
    u8 enter;               //enter索引号
    u8 back;                //back索引号
    void (*function)(void); //当前索引号对应函数
} MENU_T;

void MainInterface(void); //主界面
void BackInterface(void); //回传界面
void CalibrationInterface(void); //校准界面

void ExpertsSet(void); //专家设置
void ExpertsSet_1(void);
void ExpertsSet_2(void);
void ExpertsSet_3(void);
void ExpertsSet_4(void);
void ExpertsSet_5(void);

void GeneralSet(void); //通用设置
void GeneralSet_1(void); //语言
void GeneralSet_2(void); //主题
void GeneralSet_3(void); //声音
void GeneralSet_4(void); //模型
void GeneralSet_5(void); //遥控电池
void GeneralSet_6(void); //模型电池
void GeneralSet_7(void); //遥控低保
void GeneralSet_8(void); //模型低保

void Color_Set(u16 usBackdropCol, u16 usMainCol, u16 usMinorCol);
void button_up_callback(void *button);
void button_down_callback(void *button);
void button_enter_callback(void *button);
void button_back_callback(void *button);

#endif
