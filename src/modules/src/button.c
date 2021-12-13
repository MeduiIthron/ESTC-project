#include "stdint.h"
#include "nrfx_gpiote.h"
#include "app_timer.h"
#include "boards.h"

#include "../button.h"
#include "../logger.h"

const uint32_t DOUBLE_CLICK_TIMEOUT = APP_TIMER_TICKS(1000);
const uint32_t LONG_CLICK_TIMEOUT = APP_TIMER_TICKS(500);
const uint32_t LOCK_CLICK_TIMEOUT = APP_TIMER_TICKS(10);
const uint32_t GPIO_BUTTONS_LIST[BUTTONS_NUMBER] = BUTTONS_LIST;

APP_TIMER_DEF(DOUBLE_CLICK_TIMER);
APP_TIMER_DEF(LONG_CLICK_TIMER);
APP_TIMER_DEF(LOCK_CLICK_TIMER);

bool button_is_pressed ();
void button_double_click_timer_handler (void* context);
void button_long_click_timer_handler (void* context);
void button_lock_click_timer_handler (void* context);
void button_event_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void button_execute_handler (button_event_handler_t handler);

static button_event_handler_t handler_on_click_begin = NULL;
static button_event_handler_t handler_on_click_end = NULL;
static button_event_handler_t handler_on_long_click_begin = NULL;
static button_event_handler_t handler_on_long_click_end = NULL;
static button_event_handler_t handler_on_click = NULL;
static button_event_handler_t handler_on_double_click = NULL;
static button_event_handler_t handler_on_long_click = NULL;

static bool is_pressed = false;
static bool is_single_click = false;
static bool is_long_click = false;
static bool is_locked = false;

void button_init () {
    for (uint32_t i = 0; i < BUTTONS_NUMBER; i += 1) {
        nrf_gpio_cfg_input (GPIO_BUTTONS_LIST[i], BUTTON_PULL);
    }

    nrfx_gpiote_init();
    nrfx_gpiote_in_config_t config = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    config.pull = BUTTON_PULL;
    nrfx_gpiote_in_init(BUTTON_1, &config, &button_event_handler);
    nrfx_gpiote_in_event_enable(BUTTON_1, true);

    APP_ERROR_CHECK(app_timer_init());
    APP_ERROR_CHECK(app_timer_create(&DOUBLE_CLICK_TIMER, APP_TIMER_MODE_SINGLE_SHOT, &button_double_click_timer_handler));
    APP_ERROR_CHECK(app_timer_create(&LONG_CLICK_TIMER, APP_TIMER_MODE_SINGLE_SHOT, &button_long_click_timer_handler));
    APP_ERROR_CHECK(app_timer_create(&LOCK_CLICK_TIMER, APP_TIMER_MODE_SINGLE_SHOT, &button_lock_click_timer_handler));
}

void button_event_handler (nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
    app_timer_stop (LONG_CLICK_TIMER);
    is_pressed = button_is_pressed ();

    if (is_long_click) {
        button_execute_handler(handler_on_long_click_end);
        button_execute_handler(handler_on_long_click);
        is_long_click = false;
    }

    if (is_pressed) {
        logger_info("Button Pressed");
        app_timer_stop (DOUBLE_CLICK_TIMER);
        button_execute_handler (handler_on_click_begin);
        if (is_single_click) {
            is_single_click = false;
            button_execute_handler(handler_on_double_click);
        }
        else {
            is_single_click = true;
            app_timer_start(DOUBLE_CLICK_TIMER, DOUBLE_CLICK_TIMEOUT, NULL);
        }
        is_locked = true;
        app_timer_start(LOCK_CLICK_TIMER, LOCK_CLICK_TIMEOUT, NULL);
    }
    else {
        logger_info("Button Released");
        button_execute_handler(handler_on_click_end);
        button_execute_handler(handler_on_click);
    }
}

// Helpers
bool button_is_pressed () {
    return nrf_gpio_pin_read (GPIO_BUTTONS_LIST[0]) == BUTTONS_ACTIVE_STATE;
}

void button_double_click_timer_handler (void* context) {
    is_single_click = false;
    is_long_click = false;
    app_timer_start(LONG_CLICK_TIMER, LONG_CLICK_TIMEOUT, NULL);
}

void button_long_click_timer_handler (void* context) {
    is_long_click = button_is_pressed();
    if (is_long_click) {
        button_execute_handler(handler_on_long_click_begin);
    }
}

void button_lock_click_timer_handler (void* context) {
    is_locked = false;
}

void button_execute_handler (button_event_handler_t handler) {
    if (handler != NULL) {
        handler ();
    }
}

void button_on_click_begin (button_event_handler_t handler) {
    handler_on_click_begin = handler;
}

void button_on_click_end (button_event_handler_t handler) {
    handler_on_click_end = handler;
}

void button_on_long_click_begin (button_event_handler_t handler) {
    handler_on_long_click_begin = handler;
}

void button_on_long_click_end (button_event_handler_t handler) {
    handler_on_long_click_end = handler;
}

void button_on_click (button_event_handler_t handler) {
    handler_on_click = handler;
}

void button_on_double_click (button_event_handler_t handler) {
    handler_on_double_click = handler;
}

void button_on_long_click (button_event_handler_t handler) {
    handler_on_long_click = handler;
}