#include "./fiipTask.h"
#include "../config.h"
#include "./function.h"
#include "fiip-base/fiip.h"
#include "fiip-cloud/fiipCloud.h"
#include "fiip-link/linkUsart.h"
#include "fiip-protocol/stdp.h"
#include "pwr.h"

void onError(uint8_t err) {
  printf("stdp error code: %02X.\n", err);
}
void onGetId(uint8_t* id, uint8_t* key) {
  config_setMyId(id);
  config_setMyKey(key);
  config_setMyStatus(1, 0x89);
  pwr::reset();
}
void onLogin() {
  printf("login success.\n");

  setVar(0x01, 0);
}
void onEnterBinding(uint8_t* key) {
  printf("binding code is: %02X%02X%02X%02X.\n", key[0], key[1], key[2],
         key[3]);
}
void onBeBound(uint8_t* id, uint8_t* key) {
  printf("be bound: %02X%02X%02X%02X%02X%02X%02X%02X.\n", id[0], id[1], id[2],
         id[3], id[4], id[5], id[6], id[7]);
}
void onBeUnbound(uint8_t* id) {
  printf("be unbound: %02X%02X%02X%02X%02X%02X%02X%02X.\n", id[0], id[1], id[2],
         id[3], id[4], id[5], id[6], id[7]);
}

void onTargetChange(uint8_t* id, CloudVarStruct* var) {
  printf("cloud target: %d change %d.\n", var->keyVal[0], var->targetVal[0]);
  setVar(0x01, var->targetVal[0]);
}

void fiip_connectCloud() {
  uint8_t hostinfo[] = "2";

  LinkCfgStruct* centerServer = linkUsart_start(hostinfo, 9600);
  fiip_connect(fiip_centerId, centerServer);
}

void initFiip() {
  fiip_init();
  fiip_setId(config.myId);

  fiip_connectCloud();
  fiipCloud_init(config.myId, config.myKey);

  fiipCloud_on(CloudEvent_error, (void*)onError);
  fiipCloud_on(cloudEvent_getId, (void*)onGetId);
  fiipCloud_on(cloudEvent_login, (void*)onLogin);
  fiipCloud_on(cloudEvent_enterBinding, (void*)onEnterBinding);
  fiipCloud_on(cloudEvent_beBound, (void*)onBeBound);
  fiipCloud_on(cloudEvent_beUnbound, (void*)onBeUnbound);
  fiipCloudVar_onTargetChange(config.myId, kVal_led, 1, onTargetChange);
}
