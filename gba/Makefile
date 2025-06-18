TARGET      := libgba.a

BUILD_DIR   := build

SRC_DIR     := src
SRC_FILES   := $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES   := $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJ_FILES:.o=.d)

CC          := arm-none-eabi-gcc
CFLAGS      := -mthumb -Wall -O2
CPPFLAGS    := -MMD -MP -Iinclude
AR          := arm-none-eabi-ar
ARFLAGS     := -r -c -s

MAKEFLAGS   += --silent --no-print-directory
DIR_DUP      = mkdir -p $(@D)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^
	$(info $@ created!)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(info Compiling $< to $@...)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
.SILENT: