#ifndef APPLICATION_H
#define APPLICATION_H

#include "boards.h"

typedef struct ApplicationConfig {
    int ledRepeatSequence[LEDS_NUMBER];
    int buttonIdx;
    bool enableButton;
    bool enableLogger;
} ApplicationConfig;

void application_init (ApplicationConfig config);
void application_update ();
ApplicationConfig application_get_config ();

#endif