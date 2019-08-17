#ifndef __FIIPVARS_H
#define __FIIPVARS_H
#include "./function.h"

#define FIIPVAR_LEN 1

extern uint8_t kVal_led[FIIPVAR_LEN];
#define vLen_led 1
extern uint8_t vVal_led[vLen_led];

void fiipVars_setLed(uint8_t val);

#endif  //__FIIPVARS_H
