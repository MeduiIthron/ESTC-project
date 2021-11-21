#ifndef LED_H
#define LED_H

void led_init ();
void led_on (const uint32_t led_idx);
void led_off (const uint32_t led_idx);
void led_invert (const uint32_t led_idx);
bool led_smooth_toggle (const uint32_t led_idx, const bool isEnableDirection);

#endif