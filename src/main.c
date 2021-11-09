#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"
#include "./modules/gpio.h"

int main(void)
{
    gpio_init();

    /* Configure LEDs. */
    const int counts[4] = {6, 5, 9, 8};

    /* Toggle LEDs. */
    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++)
        {
            for (int j = 0; j < counts[i] * 2; j++) {
                gpio_led_invert(i);
                nrf_delay_ms(500);
            }
        }
    }
}
