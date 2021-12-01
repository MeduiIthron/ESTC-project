#ifndef ESTC_PROJECT_LED_H
#define ESTC_PROJECT_LED_H

void led_init ();
void led_on (const uint32_t ledIdx);
void led_off (const uint32_t ledIdx);
void led_invert (const uint32_t ledIdx);

#endif //ESTC_PROJECT_LED_H