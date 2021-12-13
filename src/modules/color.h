#ifndef ESTC_PROJECT_COLOR_H
#define ESTC_PROJECT_COLOR_H

#include "stdint.h"

typedef struct rgb_color_t {
    uint32_t red;
    uint32_t green;
    uint32_t blue;
} rgb_color_t;

typedef struct hsb_color_t {
    uint32_t hue;
    uint32_t saturation;
    uint32_t brightness;
} hsb_color_t;

rgb_color_t color_hsb_to_rgb (hsb_color_t* color);

#endif //ESTC_PROJECT_COLOR_H
