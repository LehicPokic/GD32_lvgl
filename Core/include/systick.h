#pragma once

#include <stdint.h>

void SystickConfig();
uint32_t SystickGetTick();
void SystickDelayMs(uint32_t delayMs);
void SystickUpdate();
