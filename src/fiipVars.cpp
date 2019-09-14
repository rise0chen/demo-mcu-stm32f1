#include "./fiipVars.h"
#include "fiip-base/fiip.h"
#include "fiip-cloud/fiipCloud.h"

uint8_t kVal_led[FIIPVAR_LEN] = {0x01};
uint8_t kVal_tempHumi[FIIPVAR_LEN] = {0x02};
uint8_t vVal_led[vLen_led] = {0x00};
uint8_t vVal_tempHumi[vLen_tempHumi] = {0x00, 0x00, 0x00, 0x00};

void fiipVars_setLed(uint8_t val) {
  *LED_GREEN.O = val;
  vVal_led[0] = val;
  fiipCloud_setActualVar(config.myId, config.myKey, kVal_led, FIIPVAR_LEN,
                         vVal_led, vLen_led);
}
void fiipVars_setTempHumi(uint8_t* temp, uint8_t* humi) {
  mem_cpy(&vVal_tempHumi[0], temp, 2);
  mem_cpy(&vVal_tempHumi[2], humi, 2);
  fiipCloud_setActualVar(config.myId, config.myKey, kVal_tempHumi, FIIPVAR_LEN,
                         vVal_tempHumi, vLen_tempHumi);
}
