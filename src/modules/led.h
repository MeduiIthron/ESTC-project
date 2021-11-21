<<<<<<< Updated upstream
#ifndef LED_H
#define LED_H

void led_init ();
void led_on (const uint32_t led_idx);
void led_off (const uint32_t led_idx);
void led_invert (const uint32_t led_idx);
bool led_smooth_toggle (const uint32_t led_idx, const bool isEnableDirection);

#endif
=======
#ifndef ESTC_PROJECT_LED_H
#define ESTC_PROJECT_LED_H

void led_init ();
void led_on (const uint32_t ledIdx);
void led_off (const uint32_t ledIdx);
void led_invert (const uint32_t ledIdx);
bool led_smooth_toggle (const uint32_t ledIdx, const bool isEnableDirection);

#endif //ESTC_PROJECT_LED_H
>>>>>>> Stashed changes
