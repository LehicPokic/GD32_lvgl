#ifndef STM_LVGL_MAIN_H
#define STM_LVGL_MAIN_H

#endif //STM_LVGL_MAIN_H



#include <Core/include/systick.h>
#include <gd32f4xx_rcu.h>
#include "ST7789S.h"
#include "ST7789S_driver.h"
#include "../../lv_conf.h"
#include "../../lvgl/src/lvgl.h"
#include "../../lvgl/examples/lv_examples.h"

void SdramExmcInit();


void LcdExmcInit();
void ExtMemHwInit();
void SystemClockInit();
void GpioInit();
void RtcInit();
void EnableIrq();

