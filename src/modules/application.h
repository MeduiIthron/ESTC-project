#ifndef ESTC_PROJECT_APPLICATION_H
#define ESTC_PROJECT_APPLICATION_H

#include "boards.h"

typedef struct ApplicationConfig {
    int ledRepeatSequence[LEDS_NUMBER];
    int buttonIdx;
    bool enableButton;
    bool enableLogger;
} ApplicationConfig;

typedef struct ApplicationData {
    uint32_t currentLed;
    uint32_t currentRepeats;
    bool previousIsEnableDirection;
    bool currentIsEnableDirection;
    bool enabled;
} ApplicationData;

void application_init (const ApplicationConfig* config);
void application_update ();

#endif //ESTC_PROJECT_APPLICATION_H
