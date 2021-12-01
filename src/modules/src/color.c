#include "assert.h"
#include "../color.h"

RGBColor color_hsb_to_rgb (HSBColor* color) {
    assert (color->hue >= 0 && color->hue <= 360);
    assert (color->saturation >= 0 && color->saturation <= 100);
    assert (color->brightness >= 0 && color->brightness <= 100);

    RGBColor resultColor;

    uint32_t p = color->brightness * (100 - color->saturation) / 100;
    uint32_t a = (color->brightness - p) * (color->hue % 60) / 60;
    uint32_t q = p + a;
    uint32_t t = color->brightness - a;
    uint32_t i = color->hue / 60 % 6;

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

HSBColor color_rgb_to_hsb (RGBColor* color) {
    assert(color->red >=0 && color->red <= 255);
    assert(color->green >=0 && color->green <= 255);
    assert(color->blue >=0 && color->blue <= 255);
    HSBColor result;

    double min, max, delta;
    double r, g, b;
    double h, s, v;
    r = color->red / 255;
    g = color->green / 255;
    b = color->blue / 255;

    min = r < g ? r : g;
    min = min  < b ? min  : b;

    max = r > g ? r : g;
    max = max  > b ? max : b;

    v = max;
    delta = max - min;

    if (delta < 0.00001)
    {
        s = 0;
        h = 0;
        result.hue = h * 360;
        result.saturation = s * 100;
        result.brightness = v * 100;
        return result;
    }

    if( max > 0.0 ) {
        s = (delta / max);
    } else {
        s = 0.0;
        h = 0.0;
        result.hue = h * 360;
        result.saturation = s * 100;
        result.brightness = v * 100;
        return result;
    }
    if( r >= max )
        h = ( g - b ) / delta;
    else
    if( g >= max )
        h = 2.0 + ( b - r ) / delta;
    else
        h = 4.0 + ( r - g ) / delta;
    h *= 60.0;
    if( h < 0.0 )
        h += 360.0;
    result.saturation = s * 100;
    result.brightness = v * 100;
    return result;
}