#include "nrfx_pwm.h"

#include "../led.h"
#include "../indicate_led.h"
#include "../logger.h"

#define PWM_MAX_VALUE 1000.0
#define PWM_CONFIG { \
        .output_pins  = { \
            BSP_LED_0 | NRFX_PWM_PIN_INVERTED, \
            NRFX_PWM_PIN_NOT_USED, \
            NRFX_PWM_PIN_NOT_USED, \
            NRFX_PWM_PIN_NOT_USED \
        }, \
        .irq_priority = NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY, \
        .base_clock   = (nrf_pwm_clk_t)NRFX_PWM_DEFAULT_CONFIG_BASE_CLOCK, \
        .count_mode   = (nrf_pwm_mode_t)NRFX_PWM_DEFAULT_CONFIG_COUNT_MODE, \
        .top_value    = NRFX_PWM_DEFAULT_CONFIG_TOP_VALUE, \
        .load_mode    = NRF_PWM_LOAD_INDIVIDUAL, \
        .step_mode    = (nrf_pwm_dec_step_t)NRFX_PWM_DEFAULT_CONFIG_STEP_MODE \
    }

// RGB LED pwm
static nrfx_pwm_t pwm_instance = NRFX_PWM_INSTANCE(1);
static nrfx_pwm_config_t pwm_config = PWM_CONFIG;
static nrf_pwm_values_individual_t pwm_values_channels[] = {{ 0, 0, 0, 0 }};
static nrf_pwm_values_t pwm_values;
static nrf_pwm_sequence_t pwm_sequence;

static void empty_pwm_handler (nrfx_pwm_evt_type_t eventType) {
    // Do Nothing
}

static uint16_t* brightness;

void indicate_led_init () {
    brightness = &pwm_values_channels[0].channel_0;

    pwm_values.p_individual = pwm_values_channels;
    nrfx_pwm_init (&pwm_instance, &pwm_config, empty_pwm_handler);

    pwm_sequence.values = pwm_values;
    pwm_sequence.length = NRF_PWM_VALUES_LENGTH(pwm_values_channels);
    pwm_sequence.repeats = 0;
    pwm_sequence.end_delay = 0;
}

void indicate_led_on () {
    nrfx_pwm_simple_playback (&pwm_instance, &pwm_sequence, 1, NRFX_PWM_FLAG_LOOP);
}

void indicate_led_set_brightness (const uint32_t value) {
    *brightness = (uint16_t)(((float)value) / 100 * PWM_MAX_VALUE);
}

void indicate_led_off () {
    nrfx_pwm_stop (&pwm_instance, false);
    led_off (BSP_LED_0);
}