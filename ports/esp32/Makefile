# Makefile for MicroPython on ESP32.
#
# This is a simple, convenience wrapper around idf.py (which uses cmake).

MICROPY_DIR = ../../micropython

include $(MICROPY_DIR)/py/verbose.mk


BOARD ?= LEGO_Hub
BOARD_DIR ?= boards/$(BOARD)
BUILD ?= build-LEGO_Hub
USER_C_MODULES ?= ../../../modules/micropython.cmake

# Device serial settings.
ifneq ($(PORT),)
PORT_ARG := -p $(PORT)
endif
ifneq ($(BAUD),)
BAUD_ARG := -b $(BAUD)
endif
DEVICE += $(PORT_ARG) $(BAUD_ARG)

PYTHON ?= python3

.PHONY: all clean deploy erase submodules FORCE

CMAKE_ARGS = -D MICROPY_DIR=$(abspath $(MICROPY_DIR))

ifdef USER_C_MODULES
	CMAKE_ARGS += -DUSER_C_MODULES=${USER_C_MODULES}
endif

IDFPY_FLAGS += -D MICROPY_BOARD=$(BOARD) -D MICROPY_BOARD_DIR="$(abspath $(BOARD_DIR))" $(CMAKE_ARGS)

ifdef FROZEN_MANIFEST
       IDFPY_FLAGS += -D MICROPY_FROZEN_MANIFEST=$(FROZEN_MANIFEST)
endif

ifdef BOARD_VARIANT
	IDFPY_FLAGS += -D MICROPY_BOARD_VARIANT=$(BOARD_VARIANT)
endif

ifdef MICROPY_PREVIEW_VERSION_2
	IDFPY_FLAGS += -D MICROPY_PREVIEW_VERSION_2=1
endif

ifeq ($(BUILD_VERBOSE),1)
	IDFPY_FLAGS += --verbose
endif

define RUN_IDF_PY
	$(Q)idf.py $(IDFPY_FLAGS) -B $(BUILD) $(1)
endef

all:
	$(Q)idf.py $(IDFPY_FLAGS) -B $(BUILD) build || (echo -e $(HELP_BUILD_ERROR); false)
	$(Q)$(PYTHON) makeimg.py \
		$(BUILD)/sdkconfig \
		$(BUILD)/bootloader/bootloader.bin \
		$(BUILD)/partition_table/partition-table.bin \
		$(BUILD)/micropython.bin \
		$(BUILD)/firmware.bin \
		$(BUILD)/micropython.uf2

$(BUILD)/bootloader/bootloader.bin $(BUILD)/partition_table/partition-table.bin $(BUILD)/micropython.bin: FORCE

clean:
	$(call RUN_IDF_PY,fullclean)

menuconfig:
	$(call RUN_IDF_PY,menuconfig)

deploy:
	$(call RUN_IDF_PY,$(DEVICE) flash)

erase:
	$(call RUN_IDF_PY,$(DEVICE) erase-flash)

monitor:
	$(call RUN_IDF_PY,$(DEVICE) monitor)

size:
	$(call RUN_IDF_PY,size $(SIZE_FLAGS))

size-components:
	$(call RUN_IDF_PY,size-components $(SIZE_FLAGS))

size-files:
	$(call RUN_IDF_PY,size-files)

# Run idf.py with the UPDATE_SUBMODULES flag to update
# necessary submodules for this board.
#
# This is done in a dedicated build directory as some CMake cache values are not
# set correctly if not all submodules are loaded yet.
submodules:
	$(Q)idf.py $(IDFPY_FLAGS) -B $(BUILD)/submodules -D UPDATE_SUBMODULES=1 reconfigure
