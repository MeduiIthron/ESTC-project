#ifndef ESTC_PROJECT_INDICATE_LED_H
#define ESTC_PROJECT_INDICATE_LED_H

#include "boards.h"

void indicate_led_init ();
void indicate_led_set_brightness (uint32_t brightness);
void indicate_led_on ();
void indicate_led_off ();

#endif //ESTC_PROJECT_INDICATE_LED_H
