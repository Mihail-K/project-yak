ARCH_DIR := src/arch/i686
ARCH_CFLAGS := -I $(ARCH_DIR)/include

build/libarch.a: build/boot.o build/kernel_setup.o build/console.o build/gdt.o
	$(AR) $(ARFLAGS) $@ $^

build/linker.ld: $(ARCH_DIR)/linker.ld
	cp $< $@

build/%.o: $(ARCH_DIR)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

build/%.o: $(ARCH_DIR)/%.c
	$(CC) $(CFLAGS) $(ARCH_CFLAGS) $(WARNINGS) -c $< -o $@
