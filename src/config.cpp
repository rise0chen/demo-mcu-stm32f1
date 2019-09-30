#include "./config.h"
#include "flash.h"
#include "randomSeed.h"
Config config;

void config_init() {
  static uint8_t myTypeId[TypeIdLen] = {0x00, 0x00, 0x03, 0x01};  //智能模块
  static uint8_t myTypeKey[KeyLen] = {0x7d, 0x4b, 0x99, 0x25};

  flash.read(FLASH_ADDR_START, &config, sizeof(config));  //读取设备信息
  mem_cpy(config.myTypeId, myTypeId, TypeIdLen);
  mem_cpy(config.myTypeKey, myTypeKey, KeyLen);
  if (mem_cmp(config.myId, myTypeId, 4) != 0) {
    config_reset();
  }
  if (config.myStatus[1] != 0x89) {
    config.myId[0] = (uint8_t)randomSeed() | 0x80;
    config.myId[1] = (uint8_t)randomSeed();
    config.myId[2] = (uint8_t)randomSeed();
    config.myId[3] = (uint8_t)randomSeed();
    config.myId[4] = (uint8_t)randomSeed();
    config.myId[5] = (uint8_t)randomSeed();
    config.myId[6] = (uint8_t)randomSeed();
    config.myId[7] = (uint8_t)randomSeed();
  }
}
void config_reset() {
  config_setMyStatus(0, 0x00);
  config_setMyStatus(1, 0x00);
  config_setMyStatus(0, 0x9A);
}
void config_setMyStatus(uint8_t index, uint8_t status) {
  config.myStatus[index] = status;

  flash.write(FLASH_ADDR_START, &config, sizeof(config));
}
void config_setMyId(uint8_t* id) {
  mem_cpy(config.myId, id, IdLen);
  flash.write(FLASH_ADDR_START, &config, sizeof(config));
}
void config_setMyKey(uint8_t* key) {
  mem_cpy(config.myKey, key, KeyLen);
  flash.write(FLASH_ADDR_START, &config, sizeof(config));
}
