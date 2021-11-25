#include "boards.h"
#include "assert.h"
#include "nrfx_systick.h"

#include "../led.h"

const uint32_t GPIO_LEDS_LIST[LEDS_NUMBER] = LEDS_LIST;
const uint32_t PWM_FREQUENCY_MS = 1000;
const uint32_t PWM_PERIOD_MS = 1000000 / PWM_FREQUENCY_MS;

// Smooth Led Timestamps
static nrfx_systick_state_t timer_on;
static nrfx_systick_state_t timer_off;

void led_init () {
    for (uint32_t i = 0; i < LEDS_NUMBER; i += 1) {
        nrf_gpio_cfg_output (GPIO_LEDS_LIST[i]);
        led_off (i);
    }
    nrfx_systick_get (&timer_on);
}

void led_on (const uint32_t ledIdx) {
    assert (ledIdx < LEDS_NUMBER);
    nrf_gpio_pin_write (GPIO_LEDS_LIST[ledIdx], LEDS_ACTIVE_STATE);
}

void led_off (const uint32_t ledIdx) {
    assert (ledIdx < LEDS_NUMBER);
    nrf_gpio_pin_write (GPIO_LEDS_LIST[ledIdx], !LEDS_ACTIVE_STATE);
}

void led_invert (const uint32_t ledIdx) {
    assert (ledIdx < LEDS_NUMBER);
    nrf_gpio_pin_toggle (GPIO_LEDS_LIST[ledIdx]);
}

bool led_smooth_toggle (const uint32_t ledIdx, const bool isEnableDirection) {
    // Led State
    static int time_process_start = 0;
    static int time_process_stop = PWM_PERIOD_MS;
    static bool isEnabledProcess = false;
    static bool isTickComplete = false;
    bool toggleResult = isEnableDirection;

    // Smooth toggle process
    if (nrfx_systick_test (&timer_on, time_process_start)) {
        if (!isEnabledProcess) {
            led_off (ledIdx);
            isEnabledProcess = true;
        }
        if (!isTickComplete) {
            nrfx_systick_get (&timer_off);
            isTickComplete = true;
        }
        if (nrfx_systick_test (&timer_off, time_process_stop)) {
            led_on (ledIdx);
            isEnabledProcess = false;            
            nrfx_systick_get(&timer_on);
            
            // Update Ticks Bounds
            if (isEnableDirection) {
                time_process_start += 1;
                time_process_stop -= 1;
            }
            else {                
                time_process_start -= 1;
                time_process_stop += 1;
            }

            // Complete Tick
            bool isCompleteEnableProcess = (time_process_start == PWM_PERIOD_MS && time_process_stop == 0 && isEnableDirection);
            bool isCompleteDisableProcess = (time_process_start == 0 && time_process_stop == PWM_PERIOD_MS && !isEnableDirection);
            if (isCompleteEnableProcess || isCompleteDisableProcess) {
                toggleResult = !isEnableDirection;
            }

            isTickComplete = false;
        }
    }
    return toggleResult;
}

bool led_smooth_toggle_fast (const uint32_t ledIdx, const bool isEnableDirection) {
    // Led State
    static int time_process_start = 0;
    static int time_process_stop = PWM_PERIOD_MS / 2;
    static bool isEnabledProcess = false;
    static bool isTickComplete = false;
    bool toggleResult = isEnableDirection;

    // Smooth toggle process
    if (nrfx_systick_test (&timer_on, time_process_start)) {
        if (!isEnabledProcess) {
            led_off (ledIdx);
            isEnabledProcess = true;
        }
        if (!isTickComplete) {
            nrfx_systick_get (&timer_off);
            isTickComplete = true;
        }
        if (nrfx_systick_test (&timer_off, time_process_stop)) {
            led_on (ledIdx);
            isEnabledProcess = false;
            nrfx_systick_get(&timer_on);

            // Update Ticks Bounds
            if (isEnableDirection) {
                time_process_start += 1;
                time_process_stop -= 1;
            }
            else {
                time_process_start -= 1;
                time_process_stop += 1;
            }

            // Complete Tick
            bool isCompleteEnableProcess = (time_process_start == PWM_PERIOD_MS / 2 && time_process_stop == 0 && isEnableDirection);
            bool isCompleteDisableProcess = (time_process_start == 0 && time_process_stop == PWM_PERIOD_MS / 2 && !isEnableDirection);
            if (isCompleteEnableProcess || isCompleteDisableProcess) {
                toggleResult = !isEnableDirection;
            }

            isTickComplete = false;
        }
    }
    return toggleResult;
}