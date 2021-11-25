#include "assert.h"
#include "../color.h"

RGBColor color_hsb_to_rgb (HSBColor* color) {
    assert (color->hue >= 0 && color->hue <= 360);
    assert (color->saturation >= 0 && color->saturation <= 100);
    assert (color->brightness >= 0 && color->brightness <= 100);

    RGBColor resultColor;

    unsigned int p = color->brightness * (100 - color->saturation) / 100;
    unsigned int a = (color->brightness - p) * (color->hue % 60) / 60;
    unsigned int q = p + a;
    unsigned int t = color->brightness - a;
    unsigned int i = color->hue / 60 % 6;

    switch(i) {
        case 0: {
            resultColor.red = color->brightness;
            resultColor.green = q;
            resultColor.blue = p;
            break;
        }
        case 1: {
            resultColor.red = t;
            resultColor.green = color->brightness;
            resultColor.blue = p;
            break;
        }
        case 2: {
            resultColor.red = p;
            resultColor.green = color->brightness;
            resultColor.blue = q;
            break;
        }
        case 3: {
            resultColor.red = p;
            resultColor.green = t;
            resultColor.blue = color->brightness;
            break;
        }
        case 4: {
            resultColor.red = q;
            resultColor.green = p;
            resultColor.blue = color->brightness;
            break;
        }
        case 5: {
            resultColor.red = color->brightness;
            resultColor.green = p;
            resultColor.blue = t;
            break;
        }
    }
    return resultColor;
}