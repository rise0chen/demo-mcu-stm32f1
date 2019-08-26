/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: function.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 定义用户函数
History:
        rise0chen   2018.4.26   编写注释
*************************************************/
#include "./function.h"

/*  定义全局变量(别忘记在function.h中引用)  */

/*  定义用户函数(别忘记在function.h中引用)  */
void switchLed() {
  *LED_RED.O = !(*LED_RED.I);
}
void uploadTempHumi(void) {
  dht11.getData();
  fiipVars_setTempHumi(dht11.temp, dht11.humi);
}
