#include "stdbool.h"
#include "modules/application.h"

int main (void) {
    application_init ();
    while (true) {
        application_update ();
    }
    return 0;
}