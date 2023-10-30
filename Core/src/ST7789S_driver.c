#include "ST7789S_driver.h"

#include "gd32f4xx.h"
#include "systick.h"

#include <stdarg.h>
#include <stdint.h>

#define LCD_COMMAND_BASE ((uint32_t)(0x60000000))
#define LCD_DATA_BASE    ((uint32_t)(0x60000002))
#define LCD_COMMAND      *((volatile uint16_t*)LCD_COMMAND_BASE)
#define LCD_DATA         *((volatile uint16_t*)LCD_DATA_BASE)

void LcdWriteComm(uint16_t _cmd)
{
    LCD_COMMAND = _cmd;
}

// FIXME: workaround for issue with artifacts in Pt_Change function in release
#pragma GCC push_options
#pragma GCC optimize("O0")

void LcdWriteData(uint16_t _data)
{
    LCD_DATA = _data;
}

#pragma GCC pop_options

void LcdResetPinWrite(bool value)
{
    gpio_bit_write(GPIOC, GPIO_PIN_1, value ? SET : RESET);
}

void LcdDelay(uint32_t value)
{
    SystickDelayMs(value);
}
