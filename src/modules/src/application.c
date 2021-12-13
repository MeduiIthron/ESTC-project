#include "stdint.h"
#include "stdio.h"
#include "nrfx_pwm.h"
#include "app_timer.h"

#include "../application.h"
#include "../logger.h"
#include "../led.h"
#include "../indicate_led.h"
#include "../rgb_led.h"
#include "../button.h"
#include "../memory.h"
#include "../color.h"
#include "../config.h"

#define STATE_UPDATE_DELAY_TICKS APP_TIMER_TICKS(50)

APP_TIMER_DEF(led_timer);
APP_TIMER_DEF(indicate_timer);

static application_data_t data;

void application_on_double_click ();
void application_on_long_click_begin ();
void application_on_long_click_end ();

void led_timer_handler(void *context);
void indicate_timer_handler(void *context);

void application_init () {
    data.current_state = CHANGE_OFF;
    data.indicate_brightness = 0;
    data.indicate_brightness_modifier = 1;

    /// Initialize LED Module
    led_init ();

    /// Initialize Indicate Module
    indicate_led_init ();
    indicate_led_set_brightness(data.indicate_brightness);
    indicate_led_on ();

    /// Initialize Button Module
    button_init ();
    button_on_double_click (&application_on_double_click);
    button_on_long_click_begin (&application_on_long_click_begin);
    button_on_long_click_end (&application_on_long_click_end);

    /// Check Memory
    if (MEMORY_MAKE_RESET) {
        memory_clean ();
    }

    /// Initialize RGB LED Module
    memory_load_hsb_color (&data.current_hsb_color);
    data.current_rgb_color = color_hsb_to_rgb (&data.current_hsb_color);
    rgb_led_init ();
    rgb_led_set_color (&data.current_rgb_color);
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

void application_update () {
    /// Update Log
    logger_process ();
}

// Application State Machine
void application_on_double_click () {
    if (data.current_state + 1 < APPLICATION_STATE_COUNT) {
        data.current_state += 1;
    }
    else {
        data.current_state = CHANGE_OFF;
        memory_save_hsb_color(&data.current_hsb_color);
    }
    logger_info("Double click. Switched to next state");
}

void application_on_long_click_begin () {
    app_timer_start(led_timer, STATE_UPDATE_DELAY_TICKS, NULL);
    logger_info("Long Click Begin");
}

void application_on_long_click_end () {
    app_timer_stop(led_timer);
    logger_info("Long Click End");
}

void change_hsb_color () {
    switch (data.current_state) {
        case CHANGE_HUE: {
            data.current_hsb_color.hue += 1;
            data.current_hsb_color.hue %= 361;
            break;
        }
        case CHANGE_SATURATION: {
            data.current_hsb_color.saturation += 1;
            data.current_hsb_color.saturation %= 101;
            break;
        }
        case CHANGE_BRIGHTNESS: {
            data.current_hsb_color.brightness += 1;
            data.current_hsb_color.brightness %= 101;
            break;
        }
        default: {
            break;
        }
    }
}

void blink () {
    switch (data.current_state) {
        case CHANGE_HUE: {
            data.indicate_brightness += 4 * data.indicate_brightness_modifier;
            if (data.indicate_brightness >= 100 || data.indicate_brightness <= 0)
                data.indicate_brightness_modifier *= -1;
            break;
        }
        case CHANGE_SATURATION: {
            data.indicate_brightness += 16 * data.indicate_brightness_modifier;
            if (data.indicate_brightness >= 100 || data.indicate_brightness <= 0)
                data.indicate_brightness_modifier *= -1;
            break;
        }
        case CHANGE_BRIGHTNESS: {
            data.indicate_brightness = 100;
            data.indicate_brightness_modifier = 0;
            break;
        }
        case CHANGE_OFF: {
            data.indicate_brightness = 0;
            data.indicate_brightness_modifier = 1;
            break;
        }
        default: {
            break;
        }
    }
}

void led_timer_handler(void *context) {
    change_hsb_color();
    data.current_rgb_color = color_hsb_to_rgb(&data.current_hsb_color);
    rgb_led_set_color(&data.current_rgb_color);
}

void indicate_timer_handler(void *context) {
    blink();
    indicate_led_set_brightness(data.indicate_brightness);
}