#include "nrfx_systick.h"
#include "nrfx_pwm.h"
#include "app_timer.h"

#include "../application.h"
#include "../logger.h"
#include "../led.h"
#include "../button.h"
#include "../rgb_led.h"

APP_TIMER_DEF(led_timer);

// Application Data
static ApplicationConfig config;
static ApplicationData data;
static uint32_t indicateLed;
static RGBColor currentRGBColor = {0, 0, 0};
static HSBColor currentHSBColor = { 0, 100, 100};

#define ZERO 0
#define HUE_STEP_DELAY_TICKS APP_TIMER_TICKS(50) //Blink time: 360 * 10 = 3600 ms
#define SATURATION_STEP_DELAY_TICKS APP_TIMER_TICKS(50) //Blink time: 100 * 10 = 1000 ms
#define BRIGHTNESS_STEP_DELAY_TICKS APP_TIMER_TICKS(50) //Blink time: 100 * 5 = 500 ms

void led_timer_handler(void *context);
bool test = false;

// Initialization
void application_init (const ApplicationConfig* cfg) {
    // Initialize Configuration and Data
    config = *cfg;
    data.currentState = APP_STATE_OFF;
    data.currentIsEnableDirection = true;
    data.previousIsEnableDirection = true;

    currentRGBColor = color_hsb_to_rgb(&currentHSBColor);

    // Initialize Modules
    nrfx_systick_init ();
    button_init ();
    led_init ();
    rgb_led_init ();
    if (config.enableLogger) {
        logger_init ();
    }

    // Register Callbacks
    rgb_led_set_color(&currentRGBColor);
    rgb_led_on();
    button_on_double_click(&application_next_state);
    app_timer_create(&led_timer, APP_TIMER_MODE_REPEATED, led_timer_handler);
}

// Main Loop
void application_update () {
    uint32_t state = data.currentState;

    switch (state) {
        case APP_STATE_OFF:
            led_off (indicateLed);
            break;
        case APP_STATE_CHANGE_HUE:
            data.currentIsEnableDirection = led_smooth_toggle (indicateLed, data.currentIsEnableDirection);
            if (data.previousIsEnableDirection != data.currentIsEnableDirection) {
                data.previousIsEnableDirection = data.currentIsEnableDirection;
            }
            break;
        case APP_STATE_CHANGE_SATURATION:
            data.currentIsEnableDirection = led_smooth_toggle_fast (indicateLed, data.currentIsEnableDirection);
            if (data.previousIsEnableDirection != data.currentIsEnableDirection) {
                data.previousIsEnableDirection = data.currentIsEnableDirection;
            }
            break;
        case APP_STATE_CHANGE_BRIGHTNESS:
            led_on (indicateLed);
            break;
    }

    // Update Log
    if (config.enableLogger) {
        logger_process ();
    }
    if (button_is_long_click()) {
        if (test) {
            switch (state) {
                case APP_STATE_CHANGE_HUE:
                    app_timer_start(led_timer, HUE_STEP_DELAY_TICKS, NULL);
                    break;
                case APP_STATE_CHANGE_SATURATION:
                    app_timer_start(led_timer, SATURATION_STEP_DELAY_TICKS, NULL);
                    break;
                case APP_STATE_CHANGE_BRIGHTNESS:
                    app_timer_start(led_timer, BRIGHTNESS_STEP_DELAY_TICKS, NULL);
                    break;
            }
            test = false;
        }
    }
    else {
        test = true;
        app_timer_stop(led_timer);
    }
}

// Callbacks
void application_next_state () {
    if (data.currentState + 1 < APP_STATE_COUNT) {
        data.currentState += 1;
    }
    else {
        data.currentState = 0;
    }
}

void change_hsb_color () {
    switch (data.currentState) {
        case APP_STATE_CHANGE_HUE: {
            currentHSBColor.hue += 1;
            currentHSBColor.hue %= 361;
            break;
        }
        case APP_STATE_CHANGE_SATURATION: {
            currentHSBColor.saturation += 1;
            currentHSBColor.saturation %= 101;
            break;
        }
        case APP_STATE_CHANGE_BRIGHTNESS: {
            currentHSBColor.brightness += 1;
            currentHSBColor.brightness %= 101;
            break;
        }
    }
}

void led_timer_handler(void *context) {
    change_hsb_color();
    currentRGBColor = color_hsb_to_rgb(&currentHSBColor);
    rgb_led_set_color(&currentRGBColor);
}