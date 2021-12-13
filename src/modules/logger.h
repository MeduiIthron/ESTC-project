#ifndef ESTC_PROJECT_LOGGER_H
#define ESTC_PROJECT_LOGGER_H

void logger_init ();
void logger_process ();
void logger_info (const char* msg);
void logger_error (const char* msg);
void logger_warning (const char* msg);

#endif //ESTC_PROJECT_LOGGER_H