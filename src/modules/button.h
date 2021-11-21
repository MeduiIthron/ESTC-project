#ifndef ESTC_PROJECT_BUTTON_H
#define ESTC_PROJECT_BUTTON_H

void button_init ();
void button_on_click (void (*eventHandler)(void));
void button_on_double_click (void (*eventHandler)(void));
bool button_is_pressed (const uint32_t btn_idx);

#endif //ESTC_PROJECT_BUTTON_H
