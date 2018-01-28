# rise0chen/demo-mcu-stm32f1
### 基于[C++函数库](https://gitee.com/rise0chen/lib-mcu-stm32f1)的STM32F1系列mcu的MDK5工程示例
### 通过PA0引脚AD采集，并把数据通过串口1发送给上位机。

## 引脚定义
GPIO|GPIO_Name   |GPIO_Mode|备注
:---|:-----------|:--------|:----
A0  |IN0         |模拟输入 |AD采集
A9  |USART1_TX   |开漏输出 |USART1_TX
A10 |USART1_RX   |浮空输入 |USART1_RX
 A13|SWDIO       |默认方式 |SWD下载口
 A14|SWDCLK      |默认方式 |SWD下载口
 B2 |BOOT1       |默认方式 |恒为低电平
 C14|OSC32_IN    |默认方式 |32.768K晶振输入端
 C15|OSC32_OUT   |默认方式 |32.768K晶振输出端
 D0 |OSC_IN      |默认方式 |8M晶振输入端
 D1 |OSC_OUT     |默认方式 |8M晶振输出端


## 使用步骤
``` bash
git clone -b eg.OSC git@gitee.com:rise0chen/demo-mcu-stm32f1.git
cd ./demo-mcu-stm32f1
git submodule update --init --recursive
```

## 指令集


## 备注
\r\n
0x0D 0x0A
回车 换行
