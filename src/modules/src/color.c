#include "assert.h"
#include "../color.h"

RGBColor color_hsb_to_rgb (HSBColor* color) {
    uint32_t hue = color->hue % 361;
    uint32_t saturation = color->saturation % 101;
    uint32_t brightness = color->brightness % 101;

    RGBColor resultColor;

    uint32_t p = brightness * (100 - saturation) / 100;
    uint32_t a = (brightness - p) * (hue % 60) / 60;
    uint32_t q = p + a;
    uint32_t t = brightness - a;
    uint32_t i = hue / 60 % 6;

    switch(i) {
        case 0: {
            resultColor.red = brightness;
            resultColor.green = q;
            resultColor.blue = p;
            break;
        }
        case 1: {
            resultColor.red = t;
            resultColor.green = brightness;
            resultColor.blue = p;
            break;
        }
        case 2: {
            resultColor.red = p;
            resultColor.green = brightness;
            resultColor.blue = q;
            break;
        }
        case 3: {
            resultColor.red = p;
            resultColor.green = t;
            resultColor.blue = brightness;
            break;
        }
        case 4: {
            resultColor.red = q;
            resultColor.green = p;
            resultColor.blue = brightness;
            break;
        }
        case 5: {
            resultColor.red = brightness;
            resultColor.green = p;
            resultColor.blue = t;
            break;
        }
    }
    return resultColor;
}