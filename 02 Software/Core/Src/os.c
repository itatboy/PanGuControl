/**
  ******************************************************************************
  * File Name          : os.c
  * Description        : This file provides code for the configuration
  *                      of the RTOS instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

void os_create(void * fn, int priority,int  stacksize)
{
	u8 a = 0;
	a ++;
	xTaskCreate((TaskFunction_t )fn,  
                (const char*    )"One",   
                (uint16_t       )stacksize, 
                (void*          )NULL,      
                (UBaseType_t    )priority ,       			
                (TaskHandle_t*  )&a);   				
}

void os_start(void)
{
  osKernelStart();  
}

void os_delayTick(u32 delayTick)
{
  osDelay(delayTick);
}
