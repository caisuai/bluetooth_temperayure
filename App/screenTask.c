#include "cmsis_os2.h"
#include "freertos.h"
#include "main.h"
#include "farmState.h"
#include "../BSP/oled/oled.h"
#include "../BSP/oled/font.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t getCenteredX(const char *str, uint8_t x, uint8_t width) {
  const uint8_t len = strlen(str);
  return x - (len * width) / 2;
}
void StartscreenTask(void *argument){
	
}
