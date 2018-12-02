# Macros required for the generic driver for toolchain and/or operating system.

DESIGN= trami
CONFIG= debug

OUT_DIR_CortexM0= output/$(CONFIG)/CortexM0

CC_PREFIX ?=
CC= $(CC_PREFIX) arm-none-eabi-gcc
CFLAGS_CortexM0= -mcpu=cortex-m0 -mthumb -I. -IGenerated_Source/PSoC4 -Wa,-alh=$(OUT_DIR_CortexM0)/$(basename $(<F)).lst -g -D DEBUG -Wall -ffunction-sections -ffat-lto-objects -O0

LD= arm-none-eabi-gcc
LDFLAGS_CortexM0= -mcpu=cortex-m0 -mthumb -L Generated_Source/PSoC4 -Wl,-Map,$(OUT_DIR_CortexM0)/$(DESIGN).map -T Generated_Source/PSoC4/cm0gcc.ld -specs=nano.specs -Wl,--gc-sections -g -ffunction-sections -O0 -ffat-lto-objects

AS= arm-none-eabi-as
ASFLAGS_CortexM0= -mcpu=cortex-m0 -mthumb -I. -IGenerated_Source/PSoC4 -alh=$(OUT_DIR_CortexM0)/$(basename $(<F)).lst -g -W

AR= arm-none-eabi-ar
ARFLAGS= -rs

RM= rm
RMFLAGS= -rf

CYELFTOOL= cyelftool
CYELFTOOLFLAGS= --flash_row_size 128 --flash_size 131072 --flash_offset 0x00000000 
