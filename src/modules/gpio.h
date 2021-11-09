#ifndef GPIO_H
#define GPIO_H

#include "./gpio_led/gpio_led.h"
#include "./gpio_button/gpio_button.h"

void gpio_init() { 
    gpio_leds_init();
    gpio_buttons_init();
}

#endif