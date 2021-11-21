#include "modules/application.h"

int main (void) {
    // Configuration
    const ApplicationConfig config = {
        .ledRepeatSequence = {6, 5, 9, 8},   // Led Sequence
        .buttonIdx = 0,                      // Button ID
        .enableButton = true,                // Use button?
        .enableLogger = true                 // Use Logger?
    };
    application_init (&config);

    // Main Loop
    while (true) {
        application_update ();
    }

    return 0;
}