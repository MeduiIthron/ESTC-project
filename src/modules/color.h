#ifndef ESTC_PROJECT_COLOR_H
#define ESTC_PROJECT_COLOR_H

typedef struct RGBColor {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
} RGBColor;

typedef struct HSBColor {
    unsigned int hue;
    unsigned int saturation;
    unsigned int brightness;
} HSBColor;

RGBColor color_hsb_to_rgb (HSBColor* color);

#endif //ESTC_PROJECT_COLOR_H
