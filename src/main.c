#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"
#include "./modules/gpio.h"

int main(void)
{
    gpio_init();

    /* Configure LEDs. */
    const int COUNTS[4] = {6, 5, 9, 8};
    const int DELAY = 500;

    /* Configure button */
    const int BUTTON_IDX = 0;

    /* Configure counter */
    int current_led_idx = 0;
    int current_led_repeats = 0;

    /* Toggle LEDs. */
    while (true)
    {
        bool is_pressed = gpio_button_is_pressed(BUTTON_IDX);
        if (current_led_repeats == 0) {
            current_led_repeats = COUNTS[current_led_idx] * 2;
        }

        if (is_pressed || current_led_repeats % 2 == 1) {
            /* toggle LED */
            if (current_led_repeats > 0) {
                current_led_repeats -= 1;
                gpio_led_invert(current_led_idx);
                nrf_delay_ms(DELAY);
            }

            /* update led index */
            if (current_led_repeats == 0) {
                current_led_idx += 1;
                if (current_led_idx >= LEDS_NUMBER) {
                    current_led_idx = 0;
                }
            }
        }
    }
}
