## 项目简介

该项目旨在基于STM32微控制器设计开发一款多模型遥控器，用于航模、船模及车模等模型的控制，考虑在项目后期实现PC端游戏模拟器，敬请期待。

## 硬件设计

STM32F1、2.4寸TFT彩屏、nRF24L01 2.4G无线模块

```C
/*
	电源设计
	TPS562301 7.4V转5V
	RT8059 5V转3.3V
*/
```



## 软件设计

```C
/*	
	解锁上锁 
	内八2.5秒解锁，内八1.5秒上锁
*/

/*
	数据存储
	需要存储的数据添加到_SYSPARA_T结构体，调用Para_Write()3秒后数据被存储，开机默认读取结构体内所有内容
*/

/*
	取模方式
	字符取模：楷体、逐行式、顺向、高位在前、C51格式
	图片取模：水平扫描、16位、不包含图像头数据、自左至右、自顶至底、低位在前
*/
```

## 通信协议

| 起始帧 | 功能帧 | 数据 | 校验帧 |
| :----: | :----: | :--: | :----: |
|  8位   |  8位   |  n   |  8位   |

## 进度跟踪

```C
/*
1、焊接调试
硬件问题项：
1、nRF24L01接插件线序错误，可以通过接杜邦线解决，后续改版解决。问题等级：中度
*/
```

