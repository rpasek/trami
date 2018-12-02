# Generic GNU Make driver file.
OUT_DIR= output
CONFIG= debug
GEN_SOURCE_DIR= Generated_Source/PSoC4

include platform_$(CONFIG).mk
include app_source.mk
include $(GEN_SOURCE_DIR)/gen_source.mk

GEN_OBJECTS_CortexM0= $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .o,$(basename $(GEN_C_SOURCE_CortexM0))))) $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .o,$(basename $(GEN_ASM_SOURCE_CortexM0))))) 
GEN_SEP_OBJECTS_CortexM0= $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .o,$(basename $(GEN_SEP_C_SOURCE_CortexM0))))) 
DEPS_CortexM0= $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .c.d,$(basename $(APP_C_SOURCE_CortexM0))))) $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .c.d,$(basename $(GEN_C_SOURCE_CortexM0))))) $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .c.d,$(basename $(GEN_SEP_C_SOURCE_CortexM0))))) 
APP_OBJECTS_CortexM0= $(addprefix $(OUT_DIR_CortexM0)/,$(notdir $(addsuffix .o,$(basename $(APP_C_SOURCE_CortexM0))))) 

all : $(OUT_DIR_CortexM0)/$(DESIGN).hex
prebuild_CortexM0 :
	Export/prebuild.sh

postbuild_CortexM0= Export/postbuild.sh

$(OUT_DIR_CortexM0)/$(DESIGN).hex : prebuild_CortexM0 $(OUT_DIR_CortexM0)/$(DESIGN).elf
	$(postbuild_CortexM0) $(OUT_DIR_CortexM0)/$(DESIGN).elf $(OUT_DIR_CortexM0)

$(OUT_DIR_CortexM0)/$(DESIGN).elf : $(APP_OBJECTS_CortexM0) $(GEN_SEP_OBJECTS_CortexM0) $(OUT_DIR_CortexM0)/$(DESIGN).a $(GEN_LIBS_CortexM0) $(APP_LIBS_CortexM0)
	"$(LD)" -Wl,--start-group $^ -o $@ $(LDFLAGS_CortexM0) -Wl,--end-group

$(OUT_DIR_CortexM0)/$(DESIGN).a : $(GEN_OBJECTS_CortexM0)
	"$(AR)" $(ARFLAGS) $@ $^

$(OUT_DIR_CortexM0)/%.o : $(GEN_SOURCE_DIR)/%.c
	@mkdir -p $(OUT_DIR_CortexM0)
	@"$(CC)" $(CDEPGEN_CortexM0)
	"$(CC)" -c $(CFLAGS_CortexM0) $< -o $@

$(OUT_DIR_CortexM0)/%.o : $(GEN_SOURCE_DIR)/%.s
	@mkdir -p $(OUT_DIR_CortexM0)
	"$(AS)" $(ASFLAGS_CortexM0) $< -o $@

$(OUT_DIR_CortexM0)/%.o : %.c
	@mkdir -p $(OUT_DIR_CortexM0)
	@"$(CC)" $(CDEPGEN_CortexM0)
	"$(CC)" -c $(CFLAGS_CortexM0) $< -o $@

clean:
	$(RM) $(RMFLAGS) $(OUT_DIR)
-include $(DEPS_CortexM0)
