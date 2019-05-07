#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "Can.h"
#include "Flash.h"
#include "Task.h"
#include "Usart.h"
#include "pwr.h"
#include "sys.h"
/***  引用用户函数  ***/
#include "../config.h"
#include "./FCT.h"
#include "./Ui.h"
#include "./fiipTask.h"
#include "./recvHandle.h"
#include "fiip-base/fiip.h"
#include "fiip-cloud/fiipCloud.h"
#include "fiip-protocol/stdp.h"
/***    定义IO口    ***/

/***  定义全局变量  ***/
extern uint8_t kVal_led[1];
extern uint8_t vVal_led[1];

/***  定义用户函数  ***/
void switchLed(void);
void setVar(uint8_t key, uint8_t val);

#endif  //__FUNCTION_H
