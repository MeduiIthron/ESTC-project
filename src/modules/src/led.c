#include "boards.h"
#include "assert.h"
#include "nrfx_systick.h"

#include "../led.h"
#include "../application.h"

const uint32_t gpio_leds_list[LEDS_NUMBER] = LEDS_LIST;
const uint32_t PWM_FREQUENCY = 1000;
const uint32_t PWM_PERIOD = 1000000 / PWM_FREQUENCY;

// Smooth Led Timestates
static nrfx_systick_state_t timer_on;
static nrfx_systick_state_t timer_off;

void led_init () {
    for (uint32_t i = 0; i < LEDS_NUMBER; i += 1) {
        nrf_gpio_cfg_output (gpio_leds_list[i]);
        led_off (i);
    }
    nrfx_systick_init ();
    nrfx_systick_get (&timer_on);
}

void led_on (const uint32_t led_idx) {
    assert (led_idx < LEDS_NUMBER);
    nrf_gpio_pin_write (gpio_leds_list[led_idx], LEDS_ACTIVE_STATE);
}

void led_off (const uint32_t led_idx) {
    assert (led_idx < LEDS_NUMBER);
    nrf_gpio_pin_write (gpio_leds_list[led_idx], !LEDS_ACTIVE_STATE);
}

void led_invert (const uint32_t led_idx) {
    assert (led_idx < LEDS_NUMBER);
    nrf_gpio_pin_toggle (gpio_leds_list[led_idx]);
}

bool led_smooth_toggle (const uint32_t led_idx, const bool isEnableDirection) {
    // Led State
    static int timer_process_start = 0;
    static int timer_process_stop = PWM_PERIOD;
    static bool isEnabledProcess = false;
    static bool isTickComplete = false;
    bool toggle_result = isEnableDirection;

    // Smooth toggle process
    if (nrfx_systick_test (&timer_on, timer_process_start)) {
        if (!isEnabledProcess) {
            led_off (led_idx);
            isEnabledProcess = true;
        }
        if (!isTickComplete) {
            nrfx_systick_get (&timer_off);
            isTickComplete = true;
        }
        if (nrfx_systick_test (&timer_off, timer_process_stop)) {
            led_on (led_idx);
            isEnabledProcess = false;            
            nrfx_systick_get(&timer_on);
            
            // Update Ticks Bounds
            if (isEnableDirection) {
                timer_process_start += 1;
                timer_process_stop -= 1;
            }
            else {                
                timer_process_start -= 1;
                timer_process_stop += 1;
            }

            // Complete Tick
            bool isCompleteEnableProcess = (timer_process_start == PWM_PERIOD && timer_process_stop == 0 && isEnableDirection);
            bool isCompleteDisableProcess = (timer_process_start == 0 && timer_process_stop == PWM_PERIOD && !isEnableDirection);
            if (isCompleteEnableProcess || isCompleteDisableProcess) {
                toggle_result = !isEnableDirection;
            }

            isTickComplete = false;
        }
    }
    return toggle_result;
}