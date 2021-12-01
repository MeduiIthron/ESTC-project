#ifndef ESTC_PROJECT_BUTTON_H
#define ESTC_PROJECT_BUTTON_H

void button_init ();
void button_on_click_begin (void (*eventHandler)(void));
void button_on_click_end (void (*eventHandler)(void));
void button_on_long_click_begin (void (*eventHandler)(void));
void button_on_long_click_end (void (*eventHandler)(void));
void button_on_click (void (*eventHandler)(void));
void button_on_double_click (void (*eventHandler)(void));
void button_on_long_click (void (*eventHandler)(void));

#endif //ESTC_PROJECT_BUTTON_H
