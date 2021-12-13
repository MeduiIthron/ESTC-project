#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_backend_usb.h"

#include "../logger.h"
#include "../config.h"

void logger_init () {
#ifdef LOGGER_ENABLE
    ret_code_t errCode = NRF_LOG_INIT (NULL);
    APP_ERROR_CHECK (errCode);
    NRF_LOG_DEFAULT_BACKENDS_INIT ();
#endif
}

void logger_process () {
#ifdef LOGGER_ENABLE
    LOG_BACKEND_USB_PROCESS ();
    NRF_LOG_PROCESS ();
#endif
}

void logger_info (const char* msg) {
#ifdef LOGGER_ENABLE
    NRF_LOG_INFO (msg);
#endif
}

void logger_error (const char* msg) {
#ifdef LOGGER_ENABLE
    NRF_LOG_ERROR (msg);
#endif
}

void logger_warning (const char* msg) {
#ifdef LOGGER_ENABLE
    NRF_LOG_WARNING (msg);
#endif
}
