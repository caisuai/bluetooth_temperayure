#include "cmsis_os2.h"
#include "freertos.h"
#include "main.h"
#include "farmState.h"
#include "screen.h"
#include "../BSP/oled/oled.h"
#include "../BSP/oled/font.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t getCenteredX(const char *str, uint8_t x, uint8_t width) {
  const uint8_t len = strlen(str);
  return x - (len * width) / 2;
}

static void floatToIntDec(float value,int *intpart,int *decpart){
	*intpart=(int)value;
	float decimal=value=value-(float)(*intpart);
	if(decimal<0){
		decimal=-decimal;
	}
	*decpart=(int)(decimal*10+0.5f);
	if(*decpart>10){
		*decpart=0;
		(*intpart)++;
	}else if(*decpart<0){
		*decpart=0;
	}
}

void renderHomePage(void){
	char msg[16];
	uint8_t x;
	OLED_PrintASCIIString(30, 0, " Smart Farm ", &afont12x6, OLED_COLOR_REVERSED);
	
  
  // 第一行：温度、湿度、光照强度
  // 温度显示
	OLED_PrintASCIIString(9, 14, "wendu", &afont12x6, OLED_COLOR_REVERSED);
//  OLED_PrintString(9, 14, "温度", &font12x12, OLED_COLOR_NORMAL);
  int minInt, minDec;
  floatToIntDec(farmState.temperature, &minInt, &minDec);
  sprintf(msg, "%d.%d", minInt, minDec);
  x = getCenteredX(msg, 21, 6);  // 计算居中位置（21是温度区域中心X坐标）
  sprintf(msg, "%d.%d℃", minInt, minDec);
  x = x - 6;  // 减去"℃"符号的宽度
  OLED_PrintString(x, 26, msg, &font12x12, OLED_COLOR_NORMAL);

  // 湿度显示
	OLED_PrintASCIIString(52, 14, "shidu", &afont12x6, OLED_COLOR_REVERSED);
//  OLED_PrintString(52, 14, "湿度", &font12x12, OLED_COLOR_NORMAL);
  floatToIntDec(farmState.humidity, &minInt, &minDec);
  sprintf(msg, "%d.%d%%", minInt, minDec);
  x = getCenteredX(msg, 64, 6);  // 64是湿度区域中心X坐标
  OLED_PrintString(x, 26, msg, &font12x12, OLED_COLOR_NORMAL);
}

#define RANGE_LINE_HEIGHT 12        // 每行文字的高度（像素）
#define RANGE_TEMPERATURE_Y 14      // 温度行的Y坐标
#define RANGE_TEMPERATURE_LINT_Y (RANGE_TEMPERATURE_Y + RANGE_LINE_HEIGHT -1)  // 温度行下划线Y坐标
#define RANGE_HUMIDITY_Y (RANGE_TEMPERATURE_Y + RANGE_LINE_HEIGHT + 5)  // 湿度行的Y坐标
#define RANGE_HUMIDITY_LINT_Y (RANGE_HUMIDITY_Y + RANGE_LINE_HEIGHT -1)  // 湿度行下划线Y坐标

void renderRangePage() {
  uint8_t x;
  char msg[50];
  uint8_t msgLength;
  uint8_t underlineX = 0;      // 下划线的X起始坐标
  uint8_t underlineLength = 0;  // 下划线的长度
  uint8_t underLineY = 0;       // 下划线的Y坐标

 
  
    // 第一页：显示温度、湿度、光照强度的阈值
	OLED_PrintASCIIString(25, 0, "baojing", &afont12x6, OLED_COLOR_REVERSED);
//    OLED_PrintString(25, 0, " 报警阈值 ", &font12x12, OLED_COLOR_REVERSED);
    // 显示温度阈值范围
    int minInt, minDec, maxInt, maxDec;
    floatToIntDec(farmSafeRange.mintemperature, &minInt, &minDec);
    floatToIntDec(farmSafeRange.maxtemperature, &maxInt, &maxDec);
    sprintf(msg, "%d.%d < wendu < %d.%d", minInt, minDec, maxInt, maxDec);
    msgLength = (strlen(msg) - 2) * 6;  // 计算消息总长度（减去2个中文字符，每个字符6像素宽）
    x = 64 - msgLength / 2;  // 居中显示（64是屏幕中心X坐标）
    OLED_PrintString(x, RANGE_TEMPERATURE_Y, msg, &font12x12, OLED_COLOR_NORMAL);
    
    // 如果当前选中最小温度，计算下划线位置
    if (rangeEditIndex == RANGE_EDIT_TEMPERATURE_MIN) {
      sprintf(msg, "%d.%d", minInt, minDec);
      uint8_t valueLength = strlen(msg);
      underlineX = x;
      underlineLength = valueLength * 6;
      underLineY = RANGE_TEMPERATURE_LINT_Y;
    } 
    // 如果当前选中最大温度，计算下划线位置
    else if (rangeEditIndex == RANGE_EDIT_TEMPERATURE_MAX) {
      sprintf(msg, "%d.%d", maxInt, maxDec);
      uint8_t valueLength = strlen(msg);
      underlineX = x + msgLength - valueLength * 6;  // 最大值在消息末尾
      underlineLength = valueLength * 6;
      underLineY = RANGE_TEMPERATURE_LINT_Y;
    }
  
    // 显示湿度阈值范围
    floatToIntDec(farmSafeRange.minhumidity, &minInt, &minDec);
    floatToIntDec(farmSafeRange.maxhumidity, &maxInt, &maxDec);
    sprintf(msg, "%d.%d < shidu < %d.%d", minInt, minDec, maxInt, maxDec);
    msgLength = (strlen(msg) - 2) * 6;
    x = 64 - msgLength / 2;
    OLED_PrintString(x, RANGE_HUMIDITY_Y, msg, &font12x12, OLED_COLOR_NORMAL);
    if (rangeEditIndex == RANGE_EDIT_HUMIDITY_MIN) {
      sprintf(msg, "%d.%d", minInt, minDec);
      uint8_t valueLength = strlen(msg);
      underlineX = x;
      underlineLength = valueLength * 6;
      underLineY = RANGE_HUMIDITY_LINT_Y;
    } else if (rangeEditIndex == RANGE_EDIT_HUMIDITY_MAX) {
        sprintf(msg, "%d.%d", maxInt, maxDec);
      uint8_t valueLength = strlen(msg);
      underlineX = x + msgLength - valueLength * 6;
      underlineLength = valueLength * 6;
      underLineY = RANGE_HUMIDITY_LINT_Y;
    }
  
  
  // 绘制下划线（用于指示当前选中的阈值项）
  static uint8_t flashCount = 0;  // 闪烁计数器（静态变量保持状态）
  if (underlineLength > 0) {
    if (rangeEditState == RANGE_EDIT_STATE_EDITING) {
      // 编辑模式：下划线闪烁（每10次刷新切换一次，实现闪烁效果）
      flashCount = (flashCount + 1) % 10;
      if (flashCount < 5) {
        OLED_DrawLine(underlineX, underLineY, underlineX + underlineLength, underLineY, OLED_COLOR_NORMAL);
      } 
    }else{
      // 浏览模式：下划线固定显示
      OLED_DrawLine(underlineX, underLineY, underlineX + underlineLength, underLineY, OLED_COLOR_NORMAL);
    }
  }
}
	
void StartscreenTask(void *argument){
	OLED_Init();
	for(;;){
		OLED_NewFrame();
		switch(pageIndex){
		case PAGE_HOME:
			renderHomePage();
			break;
		case PAGE_RANGE:
			renderRangePage();
			break;
		default:
			break;
		}
		
		osMutexAcquire(i2c1MutexHandle,osWaitForever);
		OLED_ShowFrame();
		osMutexRelease(i2c1MutexHandle);
		
		osDelay(10);
	}
}
