#ifndef ESTC_PROJECT_LED_H
#define ESTC_PROJECT_LED_H

void led_init ();
void led_on (const uint32_t ledIdx);
void led_off (const uint32_t ledIdx);
void led_invert (const uint32_t ledIdx);
bool led_smooth_toggle (const uint32_t ledIdx, const bool isEnableDirection);
bool led_smooth_toggle_fast (const uint32_t ledIdx, const bool isEnableDirection);

#endif //ESTC_PROJECT_LED_H