PROJECT_DIR = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SOURCES_DIR = $(PROJECT_DIR)
PROJECT_SOURCES := \
	$(SOURCES_DIR)/main.c \
	$(SOURCES_DIR)/modules/gpio_led/gpio_led.c \
	$(SOURCES_DIR)/modules/gpio_button/gpio_button.c 
