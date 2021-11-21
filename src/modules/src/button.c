#include "nrfx_gpiote.h"
#include "app_timer.h"
#include "boards.h"
#include "assert.h"

#include "../button.h"

// Buttons Config
const uint32_t GPIO_BUTTONS_LIST[BUTTONS_NUMBER] = BUTTONS_LIST;
const uint32_t BUTTON_DOUBLE_CLICK_TIMEOUT = APP_TIMER_CLOCK_FREQ;

// Event Callbacks
static void (*buttonOnClick)(void) = NULL;
static void (*buttonOnDoubleClick)(void) = NULL;

// Double Click Timer
APP_TIMER_DEF(DOUBLE_CLICK_TIMER_ID);
bool wasSingleClick = false;

void button_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void timer_evt_handler(void* context);

// Initialization
void button_init () {
    for (uint32_t i = 0; i < BUTTONS_NUMBER; i += 1) {
        nrf_gpio_cfg_input (GPIO_BUTTONS_LIST[i], BUTTON_PULL);
    }

    nrfx_gpiote_init();
    nrfx_gpiote_in_config_t config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    config.sense = NRF_GPIOTE_POLARITY_HITOLO;
    config.pull = BUTTON_PULL;
    nrfx_gpiote_in_init(BUTTON_1, &config, &button_evt_handler);
    nrfx_gpiote_in_event_enable(BUTTON_1, true);

    APP_ERROR_CHECK(app_timer_init());
    APP_ERROR_CHECK(app_timer_create(&DOUBLE_CLICK_TIMER_ID, APP_TIMER_MODE_SINGLE_SHOT, &timer_evt_handler));
}

bool button_is_pressed(const uint32_t btn_idx) {
    assert (btn_idx < BUTTONS_NUMBER);
    return nrf_gpio_pin_read (GPIO_BUTTONS_LIST[btn_idx]) == BUTTONS_ACTIVE_STATE;
}

// Event Callbacks Registry
void button_on_click (void (*eventHandler)(void)) {
    buttonOnClick = eventHandler;
}

void button_on_double_click (void (*eventHandler)(void)) {
    buttonOnDoubleClick = eventHandler;
}

// Event Handlers
void button_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
    if (action == NRF_GPIOTE_POLARITY_HITOLO){
        if (wasSingleClick) {
            buttonOnDoubleClick ();
            wasSingleClick = false;
        }
        else {
            wasSingleClick = true;
            app_timer_start(DOUBLE_CLICK_TIMER_ID, BUTTON_DOUBLE_CLICK_TIMEOUT, NULL);
        }
    }
}

void timer_evt_handler(void* context)
{
    wasSingleClick = false;
}