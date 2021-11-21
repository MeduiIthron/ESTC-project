#include "nrfx_systick.h"

#include "../application.h"
#include "../logger.h"
#include "../led.h"
#include "../button.h"

// Application Data
static ApplicationConfig config;
static ApplicationData data;

// Callbacks
void application_next_state(void);

// Initialization
void application_init (const ApplicationConfig* cfg) {
    // Initialize Configuration and Data
    config = *cfg;
    data.currentLed = 0;
    data.currentRepeats = 0;
    data.previousIsEnableDirection = true;
    data.currentIsEnableDirection = true;
    data.enabled = false;

    // Initialize Modules
    nrfx_systick_init ();
    button_init ();
    led_init ();
    if (config.enableLogger) {
        logger_init ();
    }

    // Register Callbacks
    button_on_double_click(&application_next_state);
}

// Main Loop
void application_update () {
    // Switching Led
    if (data.currentRepeats >= config.ledRepeatSequence[data.currentLed] * 2) {
        logger_log ("Switching to next LED");
        led_off (data.currentLed);
        data.currentRepeats = 0;
        data.currentLed += 1;

        if (data.currentLed >= LEDS_NUMBER)
            data.currentLed = 0;
        return;
    }

    // Toggle led if button is pressed
    if (data.enabled || !config.enableButton) {
        data.currentIsEnableDirection = led_smooth_toggle (data.currentLed, data.currentIsEnableDirection);
    }
    else {
        led_off (data.currentLed);
    }

    // Switching led data
    if (data.previousIsEnableDirection != data.currentIsEnableDirection) {
        data.previousIsEnableDirection = data.currentIsEnableDirection;
        data.currentRepeats += 1;
    }

    // Update Log
    if (config.enableLogger) {
        logger_process ();
    }
}

// Callbacks
void application_next_state () {
    data.enabled = !data.enabled;
}