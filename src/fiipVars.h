#ifndef __FIIPVARS_H
#define __FIIPVARS_H
#include "./function.h"

#define FIIPVAR_LEN 1

extern uint8_t kVal_led[FIIPVAR_LEN];
extern uint8_t kVal_tempHumi[FIIPVAR_LEN];
#define vLen_led 1
extern uint8_t vVal_led[vLen_led];
#define vLen_tempHumi 4
extern uint8_t vVal_tempHumi[vLen_tempHumi];

void fiipVars_setLed(uint8_t val);
void fiipVars_setTempHumi(uint8_t* temp, uint8_t* humi);

#endif  //__FIIPVARS_H
