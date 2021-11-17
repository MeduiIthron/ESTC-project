#ifndef BUTTON_H
#define BUTTON_H

void button_init ();
bool button_is_pressed (const uint32_t btn_idx);
bool button_is_double_click ();
void button_update ();

#endif