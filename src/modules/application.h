#ifndef ESTC_PROJECT_APPLICATION_H
#define ESTC_PROJECT_APPLICATION_H

#include "boards.h"

#define APP_STATE_COUNT 4
#define APP_STATE_OFF 0
#define APP_STATE_CHANGE_HUE 1
#define APP_STATE_CHANGE_SATURATION 2
#define APP_STATE_CHANGE_BRIGHTNESS 3

typedef struct ApplicationConfig {
    int ledRepeatSequence[LEDS_NUMBER];
    int buttonIdx;
    bool enableButton;
    bool enableLogger;
} ApplicationConfig;

typedef struct ApplicationData {
    uint32_t currentState;
    bool previousIsEnableDirection;
    bool currentIsEnableDirection;
} ApplicationData;

void application_init (const ApplicationConfig* config);
void application_update ();
void application_next_state ();

#endif //ESTC_PROJECT_APPLICATION_H
