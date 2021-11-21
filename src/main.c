#include "modules/application.h"

int main (void) {
    // Configuration
    const ApplicationConfig config = {
        {6, 5, 9, 8},           // Led Sequence
        0,                      // Button ID
        true,                   // Use button?
        true                    // Use Logger?
    };
    application_init (config);

    // Main Loop
    while (true) {
        application_update ();
    }

    return 0;
}