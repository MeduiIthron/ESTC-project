#ifndef ESTC_PROJECT_LED_H
#define ESTC_PROJECT_LED_H

typedef uint32_t led_idx_t;

void led_init ();
void led_on (const led_idx_t led_idx);
void led_off (const led_idx_t led_idx);
void led_invert (const led_idx_t led_idx);

#endif //ESTC_PROJECT_LED_H