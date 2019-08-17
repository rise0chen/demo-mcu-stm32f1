#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "flash.h"
#include "pwr.h"
#include "sys.h"
#include "task.h"
#include "usart.h"
/***  引用用户函数  ***/
#include "./bsp.h"
#include "./config.h"
#include "./fiipTask.h"
#include "./fiipVars.h"
/***    定义IO口    ***/

/***  定义全局变量  ***/

/***  定义用户函数  ***/
void switchLed(void);

#endif  //__FUNCTION_H
