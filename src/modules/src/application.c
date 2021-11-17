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
}

// Main Loop
void application_update () {
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
        return;
    }

    // Toggle led if button is pressed
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
}