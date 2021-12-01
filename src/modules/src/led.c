#include "boards.h"
#include "assert.h"

#include "../led.h"

const uint32_t GPIO_LEDS_LIST[LEDS_NUMBER] = LEDS_LIST;

void led_init () {
    for (uint32_t i = 0; i < LEDS_NUMBER; i += 1) {
        nrf_gpio_cfg_output (GPIO_LEDS_LIST[i]);
        led_off (i);
    }
}

void led_on (const uint32_t ledIdx) {
    assert (ledIdx < LEDS_NUMBER);
    nrf_gpio_pin_write (GPIO_LEDS_LIST[ledIdx], LEDS_ACTIVE_STATE);
}

void led_off (const uint32_t ledIdx) {
    assert (ledIdx < LEDS_NUMBER);
    nrf_gpio_pin_write (GPIO_LEDS_LIST[ledIdx], !LEDS_ACTIVE_STATE);
}

void led_invert (const uint32_t ledIdx) {
    assert (ledIdx < LEDS_NUMBER);
    nrf_gpio_pin_toggle (GPIO_LEDS_LIST[ledIdx]);
}