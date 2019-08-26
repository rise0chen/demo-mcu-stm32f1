#ifndef __SETUP_H
#define __SETUP_H
#include "./function.h"
#include "DHT.h"
#include "sys.h"

// GPIO
extern Gpio LED_RED;
extern Gpio LED_GREEN;
extern Gpio BTN_LED;
extern Gpio DH11_DATA;
extern DHT dht11;

void initBsp(void);

#endif  //__SETUP_H
