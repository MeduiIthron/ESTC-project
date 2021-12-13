#ifndef ESTC_PROJECT_INDICATE_LED_H
#define ESTC_PROJECT_INDICATE_LED_H

#include "stdint.h"

void indicate_led_init ();
void indicate_led_set_brightness (const uint16_t brightness);
void indicate_led_on ();
void indicate_led_off ();

#endif //ESTC_PROJECT_INDICATE_LED_H
