#include "systick.h"

#include "gd32f4xx.h"

static volatile uint32_t g_delayMsCount = 0;

void SystickConfig()
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        /* capture error */
        while (1)
        {}
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

uint32_t SystickGetTick()
{
    return g_delayMsCount;
}

void SystickDelayMs(uint32_t delayMs)
{
    uint32_t tickStart = SystickGetTick();
    uint32_t wait      = delayMs;

    /* Add a freq to guarantee minimum wait */
    if (wait == 0U)
        ++wait;

    while ((SystickGetTick() - tickStart) < wait)
        ;
}

void SystickUpdate(void)
{
    ++g_delayMsCount;
}
