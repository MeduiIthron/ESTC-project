#include "nrfx_pwm.h"

#include "../led.h"
#include "../rgb_led.h"
#include "../logger.h"

#define RGB_MAX_VALUE 255.0
#define PWM_MAX_VALUE 1000.0
#define PWM_CONFIG { \
        .output_pins  = { \
            NRFX_PWM_PIN_NOT_USED, \
            RGB_LED_RED | NRFX_PWM_PIN_INVERTED, \
            RGB_LED_GREEN | NRFX_PWM_PIN_INVERTED, \
            RGB_LED_BLUE | NRFX_PWM_PIN_INVERTED \
        }, \
        .irq_priority = NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY, \
        .base_clock   = (nrf_pwm_clk_t)NRFX_PWM_DEFAULT_CONFIG_BASE_CLOCK, \
        .count_mode   = (nrf_pwm_mode_t)NRFX_PWM_DEFAULT_CONFIG_COUNT_MODE, \
        .top_value    = NRFX_PWM_DEFAULT_CONFIG_TOP_VALUE, \
        .load_mode    = NRF_PWM_LOAD_INDIVIDUAL, \
        .step_mode    = (nrf_pwm_dec_step_t)NRFX_PWM_DEFAULT_CONFIG_STEP_MODE \
    }

// RGB LED pwm
static nrfx_pwm_t pwm_instance = NRFX_PWM_INSTANCE(0);
static nrfx_pwm_config_t pwm_config = PWM_CONFIG;
static nrf_pwm_values_individual_t pwm_values_channels[] = {{ 0, 0, 0, 0 }};
static nrf_pwm_values_t pwm_values;
static nrf_pwm_sequence_t pwm_sequence;

void empty_pwm_handler (nrfx_pwm_evt_type_t eventType) {
    // Do Nothing
}

// RGB LED Current color
static uint16_t* colorRed;
static uint16_t* colorGreen;
static uint16_t* colorBlue;

void rgb_led_init () {
    colorRed = &pwm_values_channels[0].channel_1;
    colorGreen = &pwm_values_channels[0].channel_2;
    colorBlue = &pwm_values_channels[0].channel_3;

    // Init RGB PWM
    pwm_values.p_individual = pwm_values_channels;
    nrfx_pwm_init (&pwm_instance, &pwm_config, empty_pwm_handler);

    // Start RGB PWM
    pwm_sequence.values = pwm_values;
    pwm_sequence.length = NRF_PWM_VALUES_LENGTH(pwm_values_channels);
    pwm_sequence.repeats = 0;
    pwm_sequence.end_delay = 0;
}

void rgb_led_on () {
    nrfx_pwm_simple_playback (&pwm_instance, &pwm_sequence, 1, NRFX_PWM_FLAG_LOOP);
}

void rgb_led_set_color (const RGBColor* color) {
    *colorRed = (uint16_t)(((float)color->red) / RGB_MAX_VALUE * PWM_MAX_VALUE);
    *colorGreen = (uint16_t)(((float)color->green) / RGB_MAX_VALUE * PWM_MAX_VALUE);
    *colorBlue = (uint16_t)(((float)color->blue) / RGB_MAX_VALUE * PWM_MAX_VALUE);
}

void rgb_led_off () {
    nrfx_pwm_stop (&pwm_instance, false);
    led_off (RGB_LED_RED);
    led_off (RGB_LED_GREEN);
    led_off (RGB_LED_BLUE);
}