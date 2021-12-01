#include "nrfx_systick.h"
#include "nrfx_pwm.h"
#include "app_timer.h"

#include "../application.h"
#include "../logger.h"
#include "../led.h"
#include "../button.h"
#include "../rgb_led.h"
#include "../indicate_led.h"
#include "../memory.h"

/// Application state machine
void application_on_double_click ();
void application_on_long_click_begin ();
void application_on_long_click_end ();

APP_TIMER_DEF(led_timer);
APP_TIMER_DEF(indicate_timer);

// Application Data
static ApplicationConfig config;
static ApplicationData data;
static RGBColor currentRGBColor = {0, 0, 0};
static HSBColor currentHSBColor = { 0, 100, 100};
static uint32_t indicateBrightness;
static uint32_t indicateBrightnessModifier;

#define STATE_UPDATE_DELAY_TICKS APP_TIMER_TICKS(50)

void led_timer_handler(void *context);
void indicate_timer_handler(void *context);

// Initialization
void application_init (const ApplicationConfig* cfg) {
    /// Initialize Configuration and Data
    config = *cfg;
    data.currentState = APP_STATE_OFF;
    indicateBrightness = 0;
    indicateBrightnessModifier = 1;

    /// Initialize Systick
    nrfx_systick_init ();

    /// Initialize LED Module
    led_init ();

    /// Initialize Indicate Module
    indicate_led_init ();
    indicate_led_set_brightness(indicateBrightness);
    indicate_led_on ();

    /// Initialize Button Module
    button_init ();
    button_on_double_click (&application_on_double_click);
    button_on_long_click_begin (&application_on_long_click_begin);
    button_on_click_end (&application_on_long_click_end);

    /// Initialize RGB LED Module
    memory_load_color (&currentHSBColor);
    currentRGBColor = color_hsb_to_rgb (&currentHSBColor);
    rgb_led_init ();
    rgb_led_set_color (&currentRGBColor);
    rgb_led_on ();

    /// Initialize Logger Module
    logger_init ();

    /// Initialize Blinking Timers
    app_timer_create(&led_timer, APP_TIMER_MODE_REPEATED, led_timer_handler);
    app_timer_stop(led_timer);
    app_timer_create(&indicate_timer, APP_TIMER_MODE_REPEATED, indicate_timer_handler);
    app_timer_stop(indicate_timer);
    app_timer_start(indicate_timer, STATE_UPDATE_DELAY_TICKS, NULL);
}

// Main Loop
void application_update () {
    /// Update Log
    logger_process ();
}

// Application State Machine
void application_on_double_click () {
    if (data.currentState + 1 < APP_STATE_COUNT) {
        data.currentState += 1;
    }
    else {
        data.currentState = 0;
        memory_save_color(&currentHSBColor);
    }
}

void application_on_long_click_begin () {
    app_timer_start(led_timer, STATE_UPDATE_DELAY_TICKS, NULL);
}

void application_on_long_click_end () {
    app_timer_stop(led_timer);
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

void blink () {
    switch (data.currentState) {
        case APP_STATE_CHANGE_HUE: {
            indicateBrightness += 4 * indicateBrightnessModifier;
            if (indicateBrightness >= 100 || indicateBrightness <= 0)
                indicateBrightnessModifier *= -1;
            break;
        }
        case APP_STATE_CHANGE_SATURATION: {
            indicateBrightness += 8 * indicateBrightnessModifier;
            if (indicateBrightness >= 100 || indicateBrightness <= 0)
                indicateBrightnessModifier *= -1;
            break;
        }
        case APP_STATE_CHANGE_BRIGHTNESS: {
            indicateBrightness = 100;
            indicateBrightnessModifier = 0;
            break;
        }
        case APP_STATE_OFF: {
            indicateBrightness = 0;
            indicateBrightnessModifier = 1;
            break;
        }
    }
}

void led_timer_handler(void *context) {
    change_hsb_color();
    currentRGBColor = color_hsb_to_rgb(&currentHSBColor);
    rgb_led_set_color(&currentRGBColor);
}

void indicate_timer_handler(void *context) {
    blink();
    indicate_led_set_brightness(indicateBrightness);
}