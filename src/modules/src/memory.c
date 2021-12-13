#include "stdint.h"
#include "boards.h"
#include "nrfx_nvmc.h"

#include "../memory.h"
#include "../color.h"
#include "../logger.h"

#define APP_BOOTLOADER_ADDRESS 0xE0000
#define APP_DATA_AREA_SIZE 0x3000
#define APP_MEMORY_ADDRESS (APP_BOOTLOADER_ADDRESS - APP_DATA_AREA_SIZE)

void memory_save_hsb_color (hsb_color_t* color) {
    logger_info ("saving color");
    uint32_t memoryData = 0;
    memoryData |= color->hue << 16;
    memoryData |= color->saturation << 8;
    memoryData |= color->brightness;

    memory_clean ();
    nrfx_nvmc_word_write (APP_MEMORY_ADDRESS, memoryData);
}

void memory_load_hsb_color (hsb_color_t* color) {
    logger_info ("loading color");
    uint32_t* data = (uint32_t*)APP_MEMORY_ADDRESS;
    if (*data == 0xFFFFFFFF) {
        color->hue = 0;
        color->saturation = 100;
        color->brightness = 100;
        return;
    }
    uint32_t dataValue = *data;
    color->hue = dataValue >> 16;
    color->brightness = dataValue - ((dataValue >> 8) << 8);
    color->saturation = (dataValue >> 8) - (color->hue << 8);
}

void memory_clean () {
    APP_ERROR_CHECK(nrfx_nvmc_page_erase(APP_MEMORY_ADDRESS));
}