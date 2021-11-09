#include "./gpio_led.h"
#include "boards.h"
#include "assert.h"

const uint32_t gpio_leds_list[LEDS_NUMBER] = LEDS_LIST;

void gpio_led_on(const uint32_t led_idx) {
    assert(led_idx < LEDS_NUMBER);
    nrf_gpio_pin_write(gpio_leds_list[led_idx], LEDS_ACTIVE_STATE);
}

void gpio_led_off(const uint32_t led_idx) {
    assert(led_idx < LEDS_NUMBER);
    nrf_gpio_pin_write(gpio_leds_list[led_idx], !LEDS_ACTIVE_STATE);
}

void gpio_led_invert(const uint32_t led_idx) {
    assert(led_idx < LEDS_NUMBER);
    nrf_gpio_pin_toggle(gpio_leds_list[led_idx]);
}

void gpio_leds_init() {
    for (uint32_t i = 0; i < LEDS_NUMBER; i += 1)
    {
        nrf_gpio_cfg_output(gpio_leds_list[i]);
        gpio_led_off(i);
    }
}