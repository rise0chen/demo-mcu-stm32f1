TARGET = demo-mcu-stm32f1

ROOT_DIR  := $(shell pwd)
BUILD_DIR := BUILD

C_SOURCES += $(wildcard *.c )
C_SOURCES += $(wildcard $(addsuffix /*.c, src))
C_SOURCES += $(wildcard $(addsuffix /*.c, src/function))
# C_SOURCES += $(wildcard $(addsuffix /*.c, lib/CMSIS))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/riselib))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/Common))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/system))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/hardware))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/fiip-base))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/fiip-base/link))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/fiip-base/frame))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/fiip-protocol))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/fiip-link))
C_SOURCES += $(wildcard $(addsuffix /*.c, lib/fiip-cloud))
CXX_SOURCES += $(wildcard *.cpp )
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, src))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, src/function))
# CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/CMSIS))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/riselib))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/Common))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/system))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/hardware))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/fiip-base))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/fiip-base/link))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/fiip-base/frame))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/fiip-protocol))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/fiip-link))
CXX_SOURCES += $(wildcard $(addsuffix /*.cpp, lib/fiip-cloud))
ASM_SOURCES += ./lib/CMSIS/startup/gcc/startup_stm32f10x_md.s

C_OBJECTS   += $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
CXX_OBJECTS   += $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CXX_SOURCES))
ASM_OBJECTS   += $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS   = $(C_OBJECTS) $(CXX_OBJECTS) $(ASM_SOURCES)


PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


C_DEFS += -DSTM32F10X_MD
C_DEFS += -DSTM32F103xB
C_INCLUDES += -I./src
C_INCLUDES += -I./lib
C_INCLUDES += -I./lib/riselib
C_INCLUDES += -I./lib/Common
C_INCLUDES += -I./lib/CMSIS
C_INCLUDES += -I./lib/system
C_INCLUDES += -I./lib/hardware

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = ./lib/CMSIS/startup/gcc/STM32F103C8Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# compile gcc flags
DEBUG = 1
OPT = -Og
CPU = -mcpu=cortex-m3
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
CFLAGS  += $(MCU) $(C_DEFS)  $(C_INCLUDES)  $(OPT) -Wall -fdata-sections -ffunction-sections
ASFLAGS += $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


# function: makedir rm 
ifeq ($(shell echo $$OS),$$OS)
    MAKEDIR = if not exist "$(1)" mkdir "$(1)"
    RM = rmdir /S /Q "$(1)"
else
    MAKEDIR = '$(SHELL)' -c "mkdir -p \"$(1)\""
    RM = '$(SHELL)' -c "rm -rf \"$(1)\""
endif

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
$(C_OBJECTS): $(BUILD_DIR)/%.o: %.c
	+@$(call MAKEDIR,$(dir $@))
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $^ -o $@
$(CXX_OBJECTS): $(BUILD_DIR)/%.o: %.cpp
	+@$(call MAKEDIR,$(dir $@))
	$(CXX) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $^ -o $@
$(ASM_OBJECTS): $(BUILD_DIR)/%.o: %.s
	+@$(call MAKEDIR,$(dir $@))
	$(AS) -c $(CFLAGS) $^ -o $@
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	+@$(call MAKEDIR,$(dir $@))
	$(CC) $(OBJECTS) $(LDFLAGS) -lstdc++ --specs=nosys.specs -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(BIN) $< $@

clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
