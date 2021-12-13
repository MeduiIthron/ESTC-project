#include "stdint.h"
#include "stdio.h"
#include "boards.h"

#include "../led.h"
#include "../logger.h"

const uint32_t GPIO_LEDS_LIST[LEDS_NUMBER] = LEDS_LIST;
bool led_check (const led_idx_t led_idx);

void led_init () {
    for (uint32_t i = 0; i < LEDS_NUMBER; i += 1) {
        nrf_gpio_cfg_output (GPIO_LEDS_LIST[i]);
        led_off (i);
    }
}

void led_on (const led_idx_t led_idx) {
    if (!led_check (led_idx))
        return;
    nrf_gpio_pin_write (GPIO_LEDS_LIST[led_idx], LEDS_ACTIVE_STATE);
}

void led_off (const led_idx_t led_idx) {
    if (!led_check (led_idx))
        return;
    nrf_gpio_pin_write (GPIO_LEDS_LIST[led_idx], !LEDS_ACTIVE_STATE);
}

void led_invert (const led_idx_t led_idx) {
    if (!led_check (led_idx))
        return;
    nrf_gpio_pin_toggle (GPIO_LEDS_LIST[led_idx]);
}

bool led_check (const led_idx_t led_idx) {
    if (led_idx >= LEDS_NUMBER) {
        logger_error("Invalid LED ID");
        return false;
    }
    return true;
}