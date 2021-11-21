#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_backend_usb.h"

#include "../logger.h"

void logger_init () {
<<<<<<< Updated upstream
    ret_code_t err_code = NRF_LOG_INIT (NULL);
    APP_ERROR_CHECK (err_code);
=======
    ret_code_t errCode = NRF_LOG_INIT (NULL);
    APP_ERROR_CHECK (errCode);
>>>>>>> Stashed changes
    NRF_LOG_DEFAULT_BACKENDS_INIT ();
}

void logger_process () {
    LOG_BACKEND_USB_PROCESS ();
    NRF_LOG_PROCESS ();
}

void logger_log (const char* msg) {
    NRF_LOG_INFO (msg);
}