#ifndef GPIO_H
#define GPIO_H

#include "./gpio_led/gpio_led.h"

void gpio_init() { 
    gpio_leds_init();
}

#endif