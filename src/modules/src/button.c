#include "nrfx_gpiote.h"
#include "app_timer.h"
#include "boards.h"
#include "assert.h"

#include "../button.h"
#include "../logger.h"

const uint32_t GPIO_BUTTONS_LIST[BUTTONS_NUMBER] = BUTTONS_LIST;
const uint32_t BUTTON_DOUBLE_CLICK_TIMEOUT = APP_TIMER_CLOCK_FREQ;

APP_TIMER_DEF(DOUBLE_CLICK_TIMER_ID);

void button_event_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void button_timer_event_handler(void* context);

static bool buttonIsPressed = false;
static bool buttonSingleClick = false;
static bool buttonLongClick = false;

static void (*buttonOnClickBegin)(void) = NULL;
static void (*buttonOnClickEnd)(void) = NULL;
static void (*buttonOnLongClickBegin)(void) = NULL;
static void (*buttonOnLongClickEnd)(void) = NULL;
static void (*buttonOnClick)(void) = NULL;
static void (*buttonOnDoubleClick)(void) = NULL;
static void (*buttonOnLongClick)(void) = NULL;

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
    APP_ERROR_CHECK(app_timer_create(&DOUBLE_CLICK_TIMER_ID, APP_TIMER_MODE_SINGLE_SHOT, &button_timer_event_handler));
}

void button_on_click_begin (void (*eventHandler)(void)) {
    buttonOnClickBegin = eventHandler;
}

void button_on_click_end (void (*eventHandler)(void)) {
    buttonOnClickEnd = eventHandler;
}

void button_on_long_click_begin (void (*eventHandler)(void)) {
    buttonOnLongClickBegin = eventHandler;
}

void button_on_long_click_end (void (*eventHandler)(void)) {
    buttonOnLongClickEnd = eventHandler;
}

void button_on_click (void (*eventHandler)(void)) {
    buttonOnClick = eventHandler;
}

void button_on_double_click (void (*eventHandler)(void)) {
    buttonOnDoubleClick = eventHandler;
}

void button_on_long_click (void (*eventHandler)(void)) {
    buttonOnLongClick = eventHandler;
}

void button_event_handler (nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
    buttonIsPressed = nrf_gpio_pin_read(GPIO_BUTTONS_LIST[0]) == BUTTONS_ACTIVE_STATE;

    if (buttonLongClick) {
        if (buttonOnLongClickEnd != NULL) {
            buttonOnLongClickEnd ();
        }
        if (buttonOnLongClick != NULL) {
            buttonOnLongClick ();
        }
        buttonLongClick = false;
    }
    if (buttonIsPressed) {
        app_timer_stop(DOUBLE_CLICK_TIMER_ID);
        if (buttonOnClickBegin != NULL) {
            buttonOnClickBegin ();
        }
        if (buttonSingleClick) {
            buttonSingleClick = false;
            if (buttonOnDoubleClick != NULL) {
                buttonOnDoubleClick ();
            }
        }
        else {
            buttonSingleClick = true;
            app_timer_start(DOUBLE_CLICK_TIMER_ID, BUTTON_DOUBLE_CLICK_TIMEOUT, NULL);
        }
    }
    else {
        if (buttonOnClickEnd != NULL) {
            buttonOnClickEnd ();
        }
        if (buttonOnClick != NULL) {
            buttonOnClick ();
        }
    }
}

void button_timer_event_handler (void* context) {
    buttonSingleClick = false;
    buttonLongClick = buttonIsPressed;
    if (buttonLongClick) {
        if (buttonOnLongClickBegin != NULL) {
            buttonOnLongClickBegin ();
        }
    }
}