export SHELL := /usr/bin/env bash

GAME_TITLE   := Sonic GBA

TARGET       := SonicGBA

LIBS         := gba
LIBS_TARGET  := gba/libgba.a

INCS         := include gba/include .

SRC_DIR      := src
SRC_FILES    := $(wildcard $(SRC_DIR)/*.c)

DATA_DIR     := data
DATA_FILES   := $(shell find $(DATA_DIR) -name '*.c')

BUILD_DIR    := build
OBJ_FILES    := $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_FILES    += $(DATA_FILES:$(DATA_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS         := $(OBJ_FILES:.o=.d)

VPATH        := $(SRC_DIR) $(DATA_DIR)

ARCH         := -mthumb -mthumb-interwork
SPECS        := -specs=gba.specs

CC           := arm-none-eabi-gcc
CFLAGS       := $(ARCH) -Wall -O2 -fno-strict-aliasing
CPPFLAGS     := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS      := $(addprefix -L,$(dir $(LIBS_TARGET))) $(ARCH) $(SPECS)
LDLIBS       := $(addprefix -l,$(LIBS))

MAKEFLAGS    += --silent --no-print-directory
DIR_DUP      = mkdir -p $(@D)

all: $(TARGET).gba

$(TARGET).gba: $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@
	gbafix $@ -t"$(GAME_TITLE)"

$(TARGET).elf: $(OBJ_FILES) $(LIBS_TARGET)
	$(info Linking...)
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LDLIBS) -o $@

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: %.c
	$(DIR_DUP)
	$(info Compiling $< to $@...)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(info Cleaning...)
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	rm -rf $(BUILD_DIR) $(TARGET).elf $(TARGET).gba

re:
	$(MAKE) clean
	$(MAKE) all

.PHONY: clean re
.SILENT: