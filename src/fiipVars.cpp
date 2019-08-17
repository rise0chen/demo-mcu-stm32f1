#include "./fiipVars.h"
#include "fiip-base/fiip.h"
#include "fiip-cloud/fiipCloud.h"
#include "fiip-protocol/stdp.h"

uint8_t kVal_led[FIIPVAR_LEN] = {0x01};
uint8_t vVal_led[vLen_led] = {0x00};

void fiipVars_setLed(uint8_t val) {
  *LED_GREEN.O = val;
  vVal_led[0] = val;
  fiipCloud_setActualVar(config.myId, config.myKey, kVal_led, FIIPVAR_LEN,
                         vVal_led, vLen_led);
}
