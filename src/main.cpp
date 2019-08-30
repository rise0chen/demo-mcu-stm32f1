/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: main.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 程序入口
Usage:
History:
        rise0chen   2018.4.26   编写注释
*************************************************/
#include "./bsp.h"
#include "fiip-cloud/fiipCloud.h"
#include "wdg.h"

/*************************************************
Function: setup
Description: 起始函数(仅执行1次)
*************************************************/
static void setup(void) {
  mempool_init(0x1000);
  config_init();
  delay_ms(2000);

  sysTick_init(500);  // 500ms心跳1次
  // task.add(0x01, switchLed, 10000 / task_oneTime);  // 10秒1次
  // task_start(0x02, 0xFFFF, 0, 0xFFFF);  // 执行无限次

  initFiip();
  if (config.myStatus[1] != 0x89) {  //设备初始化
    fiipCloud_getId(config.myTypeId, config.myTypeKey);
  } else {
    fiipCloud_login();
    task_add(0x02, fiipCloud_heart, 300000 / task_oneTime);
    task_start(0x02, 0xFFFF, 0, 0xFFFF);
    task_add(0x03, uploadTempHumi, 600000 / task_oneTime);
    task_start(0x03, 0xFFFF, 0, 0xFFFF);
  }

  iwdg::config(6, 1250);  // 8s
}

/*************************************************
Function: loop
Description: 循环函数(无限循环)
*************************************************/
static void loop(void) {
  iwdg::feed();
  task_run();
  flagHandle_solve();
  pwr::sleep(0);  //休眠
}

/*************************************************
Function: main
Description: 入口函数
*************************************************/
int main(void) {
  initBsp();  // 初始化底层驱动

  setup();
  while (1) {
    loop();
  }
}
