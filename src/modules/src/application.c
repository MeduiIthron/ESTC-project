<<<<<<< Updated upstream
#include "../application.h"
#include "../led.h"
#include "../button.h"
#include "../logger.h"
#include "nrfx_systick.h"

// Application State
static ApplicationConfig cfg;
static uint32_t currentLed;
static uint32_t currentRepeats;
static bool previousIsEnableDirection;
static bool currentIsEnableDirection;
static bool enabled;

// Initialization
void application_init (ApplicationConfig config) {
    cfg = config;
    nrfx_systick_init ();
    button_init ();
    led_init ();
    if (cfg.enableLogger) {
        logger_init ();
    }

    currentLed = 0;
    currentRepeats = 0;
    previousIsEnableDirection = true;
    currentIsEnableDirection = true;
    enabled = false;
=======
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
>>>>>>> Stashed changes
}

// Main Loop
void application_update () {
<<<<<<< Updated upstream
    if( button_is_double_click ())
        enabled = !enabled;

    // Switching Led
    if (currentRepeats >= cfg.ledRepeatSequence[currentLed] * 2) {
        logger_log ("Switching to next LED");
        led_off (currentLed);
        currentRepeats = 0;
        currentLed += 1;

        if (currentLed >= LEDS_NUMBER)
            currentLed = 0;
=======
    // Switching Led
    if (data.currentRepeats >= config.ledRepeatSequence[data.currentLed] * 2) {
        logger_log ("Switching to next LED");
        led_off (data.currentLed);
        data.currentRepeats = 0;
        data.currentLed += 1;

        if (data.currentLed >= LEDS_NUMBER)
            data.currentLed = 0;
>>>>>>> Stashed changes
        return;
    }

    // Toggle led if button is pressed
<<<<<<< Updated upstream
    if (enabled || !cfg.enableButton) {
        currentIsEnableDirection = led_smooth_toggle (currentLed, currentIsEnableDirection);
    }
    else {
        led_off (currentLed);
    }

    // Switching led state
    if (previousIsEnableDirection != currentIsEnableDirection) {
        previousIsEnableDirection = currentIsEnableDirection;
        currentRepeats += 1;
    }

    // Update Log
    if (cfg.enableLogger) {
        logger_process ();
    }
    button_update ();
}

ApplicationConfig application_get_config () {
    return cfg;
=======
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
>>>>>>> Stashed changes
}