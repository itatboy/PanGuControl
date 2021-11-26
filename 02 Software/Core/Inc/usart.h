#ifndef __USART_H__
#define __USART_H__
#include "sys.h"
#include "stdio.h"

#define COM0			0
#define COM1			1
#define COM2			2

/*-------------------------------------------------------------------
  名称：USART1_Init
  说明：USART1初始化
  参数：bound 波特率
  返回：void
  ------------------------------------------------------------------*/
void USART1_Init(u32 bound);

/*-------------------------------------------------------------------
  名称：USART2_Init
  说明：USART2初始化
  参数：bound 波特率
  返回：void
  ------------------------------------------------------------------*/
void USART2_Init(u32 bound);

/*-------------------------------------------------------------------
  名称：USART3_Init
  说明：USART3初始化
  参数：bound 波特率
  返回：void
  ------------------------------------------------------------------*/
void USART3_Init(u32 bound);

/*-------------------------------------------------------------------
	名称: Sys_UartSendData
  说明: 串口发送数据
	参数: ComID: COM0 COM1 COM2
				pBuffer:send buf 
				BufferLenth:send len
	返回: void
-------------------------------------------------------------------*/
int Sys_UartSendData( u8 ComID, u8* pBuffer, u16 BufferLenth );

/*-------------------------------------------------------------------
	名称: Sys_UartRecvData
  说明: 串口接收数据
	参数: ComID: COM0 COM1 COM2
				pBuffer:send buf 
				BufferLenth:send len
				timeout：
	返回: void
-------------------------------------------------------------------*/
int Sys_UartRecvData(u8 ComID, u8 *pBuffer, u16 BufferLenth, u32 timeout );

/*-------------------------------------------------------------------
	名称: Sys_UartClearBuffer
  说明: 串口置零
	参数: ComID: COM0 COM1 COM2
	返回: void
-------------------------------------------------------------------*/
int Sys_UartClearBuffer(u8 ComID);

/*-------------------------------------------------------------------
	名称: Sys_UartMode
  说明: 串口模式选择
	参数: uctx: 1 OR 0
				ucrx：1 OR 0
	返回: void
-------------------------------------------------------------------*/
int Sys_UartMode(u8 uctx,u8 ucrx);

#endif
