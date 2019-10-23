ARCH_DIR     := src/arch/i686
ARCH_INCLUDE := $(ARCH_DIR)/include

ARCH_ASMSOURCES := $(shell find $(ARCH_DIR) -type f -name "*.asm")
ARCH_ASMOBJECTS := $(patsubst $(ARCH_DIR)/%.asm,build/%.o,$(ARCH_ASMSOURCES))

ARCH_CFLAGS   	:= -I $(ARCH_INCLUDE)
ARCH_CTEMPLATES := $(shell find $(ARCH_DIR) -type f -name "*.c.sh")
ARCH_CARTIFACTS := $(patsubst %.c.sh,%.c,$(ARCH_CTEMPLATES))
ARCH_CSOURCES 	:= $(shell find $(ARCH_DIR) -type f -name "*.c") $(ARCH_CARTIFACTS)
ARCH_CHEADERS 	:= $(shell find $(ARCH_INCLUDE) -type f -name "*.h")
ARCH_COBJECTS 	:= $(patsubst $(ARCH_DIR)/%.c,build/%.o,$(ARCH_CSOURCES))
ARCH_CDEPS    	:= $(patsubst build/%.o,build/%.d,$(ARCH_COBJECTS))

arch_clean:
	rm -f $(ARCH_CARTIFACTS)

build/libarch.a: build/boot.o $(ARCH_ASMOBJECTS) $(ARCH_COBJECTS)
	$(AR) $(ARFLAGS) $@ $^

build/linker.ld: $(ARCH_DIR)/linker.ld
	cp $< $@

build/%.o: $(ARCH_DIR)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

build/%.o: $(ARCH_DIR)/%.c
	$(CC) $(CFLAGS) $(ARCH_CFLAGS) $(WARNINGS) -MMD -MP -c $< -o $@

$(ARCH_DIR)/%.c: $(ARCH_DIR)/%.c.sh
	$< > $@

-include $(ARCH_CDEPS)
