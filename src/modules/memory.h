#ifndef ESTC_PROJECT_MEMORY_H
#define ESTC_PROJECT_MEMORY_H

#include "color.h"

void memory_clean ();
void memory_save_hsb_color (hsb_color_t* color);
void memory_load_hsb_color (hsb_color_t* color);

#endif //ESTC_PROJECT_MEMORY_H
