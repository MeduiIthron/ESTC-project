#ifndef LOGGER_H
#define LOGGER_H

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_backend_usb.h"

void logger_init ();
void logger_process ();
void logger_log (const char* msg);

#endif