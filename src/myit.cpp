#include "./function.h"
#include "it.h"

void EXTI9_5_IRQHandler(void) {
  uint32_t pr = EXTI->PR;
  if (pr & (1 << 5)) {
    delay_ms(100);          //消抖
    if (*BTN_LED.I == 1) {  // 按键中断
      fiipVars_setLed(!vVal_led[0]);
    }
    EXTI->PR = 1 << 5;
  }
}
