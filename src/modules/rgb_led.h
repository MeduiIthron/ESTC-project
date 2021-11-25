#ifndef ESTC_PROJECT_RGB_LED_H
#define ESTC_PROJECT_RGB_LED_H

#include "boards.h"
#include "color.h"

#define RGB_LED_RED BSP_LED_1
#define RGB_LED_GREEN BSP_LED_2
#define RGB_LED_BLUE BSP_LED_3

void rgb_led_init ();
void rgb_led_on ();
void rgb_led_set_color (const RGBColor* color);
void rgb_led_off ();

#endif //ESTC_PROJECT_RGB_LED_H
