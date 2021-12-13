#ifndef ESTC_PROJECT_BUTTON_H
#define ESTC_PROJECT_BUTTON_H

typedef void (*button_event_handler_t) (void);

void button_init ();
void button_on_click_begin (button_event_handler_t handler);
void button_on_click_end (button_event_handler_t handler);
void button_on_long_click_begin (button_event_handler_t handler);
void button_on_long_click_end (button_event_handler_t handler);
void button_on_click (button_event_handler_t handler);
void button_on_double_click (button_event_handler_t handler);
void button_on_long_click (button_event_handler_t handler);

#endif //ESTC_PROJECT_BUTTON_H
