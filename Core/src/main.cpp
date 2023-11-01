
extern "C" {
#include <gd32f4xx_rcu.h>
#include <Core/include/systick.h>
}
#include <Core/include/main.h>
#include <cstdint>
#include "ST7789S.h"
#include "ST7789S_driver.h"
#include "../../lv_conf.h"
#include "../../lvgl/src/lvgl.h"
#include "../../lvgl/examples/lv_examples.h"


int main(void) {
    SystemClockInit();
    GpioInit();
    RtcInit();
    EnableIrq();
    ExtMemHwInit();

    lv_init();

    //ST7789S_Init();
    //ST7789S_FillArea(100, 100, 200, 200, 0x03A2);
    Display_Init();

    lv_example_get_started_1();

    while (1) {
        lv_timer_handler_run_in_period(5);
    }
}



//Init Exmc

void SdramExmcInit() {
    constexpr auto SDRAM_DEVICE = EXMC_SDRAM_DEVICE0;

    /* Burst Length */
    constexpr std::uint16_t SDRAM_MODEREG_BURST_LENGTH_1 = 0x0000U;
    /* Burst Type */
    constexpr std::uint16_t SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL = 0x0000U;
    /* CAS Latency */
    constexpr std::uint16_t SDRAM_MODEREG_CAS_LATENCY_3 = 0x0030U;
    /* Write Mode */
    constexpr std::uint16_t SDRAM_MODEREG_WRITEBURST_MODE_SINGLE = 0x0200U;
    constexpr std::uint16_t SDRAM_MODEREG_OPERATING_MODE_STANDARD = 0x0000U;
    constexpr std::uint32_t SDRAM_TIMEOUT = 0x0000FFFFU;

    /* enable EXMC clock */

    rcu_periph_clock_enable(RCU_EXMC);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    /* common GPIO configuration */
    /* SDNWE(PC0), SDNE0(PC2),SDCKE0(PC3) pin configuration */
    gpio_af_set(GPIOC, GPIO_AF_12, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);

    /* D2(PD0),D3(PD1),D13(PD8),D14(PD9),D15(PD10),D0(PD14),D1(PD15) pin configuration */
    gpio_af_set(GPIOD, GPIO_AF_12,
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
                GPIO_PIN_15);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
                  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
                  GPIO_PIN_15);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                            GPIO_PIN_14 | GPIO_PIN_15);

    /*
    NBL0(PE0),NBL1(PE1),D4(PE7),D5(PE8),D6(PE9),D7(PE10),D8(PE11),D9(PE12),D10(PE13),D11(PE14),D12(PE15)
     * pin configuration */
    gpio_af_set(GPIOE, GPIO_AF_12,
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
                  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                  GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
                            GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
                            GPIO_PIN_14 | GPIO_PIN_15);

    /*
    A0(PF0),A1(PF1),A2(PF2),A3(PF3),A4(PF4),A5(PF5),NRAS(PF11),A6(PF12),A7(PF13),A8(PF14),A9(PF15)
     * pin configuration */
    gpio_af_set(GPIOF, GPIO_AF_12,
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
                GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
                  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
                  GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
                            GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                            GPIO_PIN_15);

    /* A10(PG0),A11(PG1),A12(PG2),A14(PG4),A15(PG5),SDCLK(PG8),NCAS(PG15) pin configuration */
    gpio_af_set(GPIOG, GPIO_AF_12,
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 |
                GPIO_PIN_15);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
                  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 |
                  GPIO_PIN_15);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 |
                            GPIO_PIN_8 | GPIO_PIN_15);

    /* specify which SDRAM to read and write */
    std::uint32_t bank_select = 0;
    if (SDRAM_DEVICE == EXMC_SDRAM_DEVICE0)
        bank_select = EXMC_SDRAM_DEVICE0_SELECT;
    else
        bank_select = EXMC_SDRAM_DEVICE1_SELECT;

    /* EXMC SDRAM device initialization sequence --------------------------------*/
    /* Step 1 : configure SDRAM timing registers --------------------------------*/
    exmc_sdram_timing_parameter_struct sdram_timing_init_struct{};
    /* LMRD: 2 clock cycles */
    sdram_timing_init_struct.load_mode_register_delay = 2;
    /* XSRD: min = 67ns */
    sdram_timing_init_struct.exit_selfrefresh_delay = 5;
    /* RASD: min=42ns , max=120k (ns) */
    sdram_timing_init_struct.row_address_select_delay = 3;
    /* ARFD: min=60ns */
    sdram_timing_init_struct.auto_refresh_delay = 4;
    /* WRD:  min=1 Clock cycles +6ns */
    sdram_timing_init_struct.write_recovery_delay = 2;
    /* RPD:  min=18ns */
    sdram_timing_init_struct.row_precharge_delay = 2;
    /* RCD:  min=18ns */
    sdram_timing_init_struct.row_to_column_delay = 2;

    /* step 2 : configure SDRAM control registers ---------------------------------*/
    exmc_sdram_parameter_struct sdram_init_struct{};
    sdram_init_struct.sdram_device = SDRAM_DEVICE;
    sdram_init_struct.column_address_width = EXMC_SDRAM_COW_ADDRESS_8;
    sdram_init_struct.row_address_width = EXMC_SDRAM_ROW_ADDRESS_12;
    sdram_init_struct.data_width = EXMC_SDRAM_DATABUS_WIDTH_16B;
    sdram_init_struct.internal_bank_number = EXMC_SDRAM_4_INTER_BANK;
    sdram_init_struct.cas_latency = EXMC_CAS_LATENCY_3_SDCLK;
    sdram_init_struct.write_protection = DISABLE;
    sdram_init_struct.sdclock_config = EXMC_SDCLK_PERIODS_3_HCLK;
    sdram_init_struct.burst_read_switch = ENABLE;
    sdram_init_struct.pipeline_read_delay = EXMC_PIPELINE_DELAY_2_HCLK;
    sdram_init_struct.timing = &sdram_timing_init_struct;
    /* EXMC SDRAM bank initialization */
    exmc_sdram_init(&sdram_init_struct);

    /* step 3 : configure CKE high command---------------------------------------*/
    exmc_sdram_command_parameter_struct sdram_command_init_struct{};
    sdram_command_init_struct.command = EXMC_SDRAM_CLOCK_ENABLE;
    sdram_command_init_struct.bank_select = bank_select;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    std::uint32_t timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(SDRAM_DEVICE, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 4 : insert 10ms delay----------------------------------------------*/
    SystickDelayMs(10);

    /* step 5 : configure precharge all command----------------------------------*/
    sdram_command_init_struct.command = EXMC_SDRAM_PRECHARGE_ALL;
    sdram_command_init_struct.bank_select = bank_select;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(SDRAM_DEVICE, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 6 : configure Auto-Refresh command-----------------------------------*/
    sdram_command_init_struct.command = EXMC_SDRAM_AUTO_REFRESH;
    sdram_command_init_struct.bank_select = bank_select;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_4_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(SDRAM_DEVICE, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 7 : configure load mode register command-----------------------------*/
    /* program mode register */
    sdram_command_init_struct.command = EXMC_SDRAM_LOAD_MODE_REGISTER;
    sdram_command_init_struct.bank_select = bank_select;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    sdram_command_init_struct.mode_register_content =
            SDRAM_MODEREG_BURST_LENGTH_1 | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
            SDRAM_MODEREG_CAS_LATENCY_3 | SDRAM_MODEREG_OPERATING_MODE_STANDARD |
            SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(SDRAM_DEVICE, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 8 : set the auto-refresh rate counter--------------------------------*/
    /* 64ms, 8192-cycle refresh, 64ms/8192=7.81us */
    /* SDCLK_Freq = SYS_Freq/3 */
    /* (7.81 us * SDCLK_Freq) - 20 */
    exmc_sdram_refresh_count_set(501);

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(SDRAM_DEVICE, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
}

//Init LcdExmc
void LcdExmcInit() {
    /* EXMC clock enable */
    rcu_periph_clock_enable(RCU_EXMC);

    /* configure GPIO D[0-15] */
    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_af_set(GPIOD, GPIO_AF_12,
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
                GPIO_PIN_15);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
                  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
                  GPIO_PIN_15);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                            GPIO_PIN_14 | GPIO_PIN_15);

    rcu_periph_clock_enable(RCU_GPIOE);
    gpio_af_set(GPIOE, GPIO_AF_12,
                GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
                  GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                            GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* configure GPIO A[0] */
    rcu_periph_clock_enable(RCU_GPIOF);
    gpio_af_set(GPIOF, GPIO_AF_12, GPIO_PIN_0);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    /* configure NOE(PD4) NWE(PD5) NE0(PD7) */
    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_4);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_4);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);

    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_5);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_5);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);

    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_7);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

    /* configure timing parameter */
    exmc_norsram_timing_parameter_struct nor_timing_init_struct{};
    nor_timing_init_struct.asyn_access_mode = EXMC_ACCESS_MODE_A;
    nor_timing_init_struct.syn_data_latency = EXMC_DATALAT_2_CLK;
    nor_timing_init_struct.syn_clk_division = EXMC_SYN_CLOCK_RATIO_DISABLE;
    nor_timing_init_struct.bus_latency = 0;
    nor_timing_init_struct.asyn_data_setuptime = 4;
    nor_timing_init_struct.asyn_address_holdtime = 0;
    nor_timing_init_struct.asyn_address_setuptime = 4;

    /* configure EXMC bus parameters */
    exmc_norsram_parameter_struct nor_init_struct;
    nor_init_struct.norsram_region = EXMC_BANK0_NORSRAM_REGION0;
    nor_init_struct.write_mode = EXMC_ASYN_WRITE;
    nor_init_struct.extended_mode = DISABLE;
    nor_init_struct.asyn_wait = DISABLE;
    nor_init_struct.nwait_signal = DISABLE;
    nor_init_struct.memory_write = ENABLE;
    nor_init_struct.nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
    nor_init_struct.wrap_burst_mode = DISABLE;
    nor_init_struct.nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
    nor_init_struct.burst_mode = DISABLE;
    nor_init_struct.databus_width = EXMC_NOR_DATABUS_WIDTH_16B;
    nor_init_struct.memory_type = EXMC_MEMORY_TYPE_PSRAM;
    nor_init_struct.address_data_mux = DISABLE;
    nor_init_struct.read_write_timing = &nor_timing_init_struct;
    nor_init_struct.write_timing = &nor_timing_init_struct;
    exmc_norsram_init(&nor_init_struct);

    /* enable the EXMC bank0 NORSRAM */
    exmc_norsram_enable(EXMC_BANK0_NORSRAM_REGION0);
}

void ExtMemHwInit() {
    SdramExmcInit();
    LcdExmcInit();
}

void SystemClockInit() {
#ifdef NDEBUG
    SCB->VTOR = 0x08010200;
#endif
    // init systick timer
    SystickConfig();

#ifdef NDEBUG
    // init Watchdog timer
    /* confiure FWDGT counter clock: 32KHz(IRC32K) / 32 = 1 KHz */
    /* After 4 seconds to generate a reset */
    fwdgt_config(4095, FWDGT_PSC_DIV32);
    fwdgt_enable();
#endif
}

void GpioInit() {
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);

    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_bit_set(GPIOA, GPIO_PIN_1);
    // LCD RESET config (PC1)
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_bit_set(GPIOC, GPIO_PIN_1);

    // SDRAM PWR ON config (PB9)
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_bit_reset(GPIOB, GPIO_PIN_9); // Enable SDRAM power

    // PWR_LATCH config (PC10)
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_bit_set(GPIOC, GPIO_PIN_10); // Enable power latch

    // PWR_KEY_STATE (PA15)
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_15);

    // CHARGE_STATE2 (PA9)
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);

    // CHARGE_STATE1 (PA10)
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_10);

    // USB_PRESENCE, charge
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);

    // LIGHT/FULL version (PB13)
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
}

void RtcInit() {
    constexpr auto BKP_VALUE = 0x32F1;

    /* enable access to RTC registers in Backup domain */
    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();

    /* configure RTC clock */
    rcu_osci_on(RCU_LXTAL);
    rcu_osci_stab_wait(RCU_LXTAL);
    rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);

    rcu_periph_clock_enable(RCU_RTC);
    rtc_register_sync_wait();

    /* get RTC clock entry selection */
    const auto rtcsrcFlag = GET_BITS(RCU_BDCTL, 8, 9);
    /* check if RTC has aready been configured */
    if ((BKP_VALUE != RTC_BKP0) || (0x00 == rtcsrcFlag)) {
        /* backup data register value is not correct or not yet programmed
        or RTC clock source is not configured (when the first time the program
        is executed or data in RCU_BDCTL is lost due to Vbat feeding) */

        /* setup RTC time value */
        rtc_parameter_struct rtc_initpara{};
        rtc_initpara.factor_asyn = 0x7FU;
        rtc_initpara.factor_syn = 0xFFU;
        rtc_initpara.year = 0x00U;
        rtc_initpara.day_of_week = 0x01U;
        rtc_initpara.month = 0x01U;
        rtc_initpara.date = 0x01U;
        rtc_initpara.display_format = RTC_24HOUR;
        rtc_initpara.am_pm = RTC_AM;
        rtc_initpara.hour = 0x00U;
        rtc_initpara.minute = 0x00U;
        rtc_initpara.second = 0x00U;
        /* RTC current time configuration */

    }
}

void EnableIrq() {
    __enable_irq();
}

extern "C" void SysTick_Handler(void) {
    SystickUpdate();
    lv_tick_inc(1);
}
