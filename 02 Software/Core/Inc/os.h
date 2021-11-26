#ifndef __OS_H
#define __OS_H
#include "main.h"

void os_create(void * fn, int priority,int  stacksize);

void os_start(void);

void os_delayTick(u32 delayTick);

#endif
