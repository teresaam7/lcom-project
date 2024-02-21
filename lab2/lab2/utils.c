#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if (!lb){
    return 1;
  }
  *lsb = val & 0xFF;
  return 0; 
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (!msb){
    return 1;
  }
  *msb = val >> 8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if (!value || sys_inb(port, value) != 0){
    return 1;
  }
  uint32_t *temp;
  *value = *temp & 0xFF;
  return 0;
}
