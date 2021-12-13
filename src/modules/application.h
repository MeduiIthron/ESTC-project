#ifndef ESTC_PROJECT_APPLICATION_H
#define ESTC_PROJECT_APPLICATION_H

#include "stdint.h"
#include "color.h"

typedef enum application_state_t {
    CHANGE_OFF = 0,
    CHANGE_HUE = 1,
    CHANGE_SATURATION = 2,
    CHANGE_BRIGHTNESS = 3
} application_state_t;

#define APPLICATION_STATE_COUNT 4

typedef struct application_data_t {
    application_state_t current_state;
    rgb_color_t current_rgb_color;
    hsb_color_t current_hsb_color;
    uint16_t indicate_brightness;
    uint16_t indicate_brightness_modifier;
} application_data_t;

void application_init ();
void application_update ();

#endif //ESTC_PROJECT_APPLICATION_H
