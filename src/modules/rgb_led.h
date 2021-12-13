#ifndef ESTC_PROJECT_RGB_LED_H
#define ESTC_PROJECT_RGB_LED_H

#include "color.h"

void rgb_led_init ();
void rgb_led_on ();
void rgb_led_set_color (const rgb_color_t* color);
void rgb_led_off ();

#endif //ESTC_PROJECT_RGB_LED_H
