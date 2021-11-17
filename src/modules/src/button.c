#include "boards.h"
#include "assert.h"

#include "../button.h"

const uint32_t gpio_buttons_list[BUTTONS_NUMBER] = BUTTONS_LIST;

void button_init () {
    for (uint32_t i = 0; i < BUTTONS_NUMBER; i += 1) {
        nrf_gpio_cfg_input (gpio_buttons_list[i], BUTTON_PULL);
    }
}

bool button_is_pressed(const uint32_t btn_idx) {
    assert (btn_idx < BUTTONS_NUMBER);
    return nrf_gpio_pin_read (gpio_buttons_list[btn_idx]) == BUTTONS_ACTIVE_STATE;
}