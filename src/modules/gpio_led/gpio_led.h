#ifndef GPIO_LED_H
#define GPIO_LED_H 

#include "boards.h"

void gpio_leds_init();
void gpio_led_on(const uint32_t led_idx);
void gpio_led_off(const uint32_t led_idx);
void gpio_led_invert(const uint32_t led_idx);

#endif