#ifndef ESTC_PROJECT_COLOR_H
#define ESTC_PROJECT_COLOR_H

#include "boards.h"

typedef struct RGBColor {
    uint32_t red;
    uint32_t green;
    uint32_t blue;
} RGBColor;

typedef struct HSBColor {
    uint32_t hue;
    uint32_t saturation;
    uint32_t brightness;
} HSBColor;

RGBColor color_hsb_to_rgb (HSBColor* color);
HSBColor color_rgb_to_hsb (RGBColor* color);

#endif //ESTC_PROJECT_COLOR_H
