#include "modules/application.h"

int main (void) {
    // Configuration
    const ApplicationConfig config = {
<<<<<<< Updated upstream
        {6, 5, 9, 8},           // Led Sequence
        0,                      // Button ID
        true,                   // Use button?
        true                    // Use Logger?
    };
    application_init (config);
=======
        .ledRepeatSequence = {6, 5, 9, 8},   // Led Sequence
        .buttonIdx = 0,                      // Button ID
        .enableButton = true,                // Use button?
        .enableLogger = true                 // Use Logger?
    };
    application_init (&config);
>>>>>>> Stashed changes

    // Main Loop
    while (true) {
        application_update ();
    }

    return 0;
}