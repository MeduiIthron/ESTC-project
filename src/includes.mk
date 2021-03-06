PROJECT_DIR = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SOURCES_DIR = $(PROJECT_DIR)
PROJECT_SOURCES := \
	$(SOURCES_DIR)/main.c \
	$(SOURCES_DIR)/modules/src/application.c \
	$(SOURCES_DIR)/modules/src/memory.c \
	$(SOURCES_DIR)/modules/src/color.c \
	$(SOURCES_DIR)/modules/src/button.c \
	$(SOURCES_DIR)/modules/src/led.c \
	$(SOURCES_DIR)/modules/src/rgb_led.c \
	$(SOURCES_DIR)/modules/src/indicate_led.c \
	$(SOURCES_DIR)/modules/src/logger.c
