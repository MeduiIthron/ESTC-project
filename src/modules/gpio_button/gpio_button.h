#ifndef GPIO_BUTTON_H
#define GPIO_BUTTON_H

#include "boards.h"

void gpio_buttons_init();
bool gpio_button_is_pressed(uint32_t btn_idx);

#endif