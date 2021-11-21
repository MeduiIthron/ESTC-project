<<<<<<< Updated upstream
#ifndef BUTTON_H
#define BUTTON_H

void button_init ();
bool button_is_pressed (const uint32_t btn_idx);
bool button_is_double_click ();
void button_update ();

#endif
=======
#ifndef ESTC_PROJECT_BUTTON_H
#define ESTC_PROJECT_BUTTON_H

void button_init ();
void button_on_click (void (*eventHandler)(void));
void button_on_double_click (void (*eventHandler)(void));
bool button_is_pressed (const uint32_t btn_idx);

#endif //ESTC_PROJECT_BUTTON_H
>>>>>>> Stashed changes
