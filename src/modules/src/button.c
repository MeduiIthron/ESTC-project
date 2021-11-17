#include "boards.h"
#include "assert.h"
#include "nrfx_gpiote.h"
#include "nrfx_systick.h"

#include "../button.h"
#include "../led.h"

const uint32_t gpio_buttons_list[BUTTONS_NUMBER] = BUTTONS_LIST;

// Double Click State
bool wasSingleClick = false;
bool wasDoubleClick = false;
int tick = 0;
nrfx_systick_state_t double_click_timer;

void button_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
    if (action == NRF_GPIOTE_POLARITY_HITOLO){
        if (wasSingleClick) {
            wasDoubleClick = true;
            wasSingleClick = false;
        }
        else {
            wasSingleClick = true;
            nrfx_systick_get(&double_click_timer);
        }
    }
}

void button_init () {
    for (uint32_t i = 0; i < BUTTONS_NUMBER; i += 1) {
        nrf_gpio_cfg_input (gpio_buttons_list[i], BUTTON_PULL);
    }

    nrfx_gpiote_init();
    nrfx_gpiote_in_config_t config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    config.sense = NRF_GPIOTE_POLARITY_HITOLO;
    config.pull = BUTTON_PULL;
    nrfx_gpiote_in_init(BUTTON_1, &config, &button_evt_handler);
    nrfx_gpiote_in_event_enable(BUTTON_1, true);
    nrfx_systick_get(&double_click_timer);
}

bool button_is_pressed(const uint32_t btn_idx) {
    assert (btn_idx < BUTTONS_NUMBER);
    return nrf_gpio_pin_read (gpio_buttons_list[btn_idx]) == BUTTONS_ACTIVE_STATE;
}

bool button_is_double_click () {
    if (wasDoubleClick) {
        wasDoubleClick = false;
        wasSingleClick = false;
        return true;
    }
    return false;
}

void button_update () {
    if (wasSingleClick && tick == 1000) {
        wasSingleClick = false;
        wasDoubleClick = false;
    }
    else if (wasSingleClick && nrfx_systick_test(&double_click_timer, 1000) && tick < 1000) {
        nrfx_systick_get(&double_click_timer);
        tick += 1;
    }
    if (!wasSingleClick) {
        tick = 0;
    }
}