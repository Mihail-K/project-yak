ARFLAGS := rcs

ASM      := nasm
ASMFLAGS := -felf32

CC 		  := clang
CFLAGS 	  := --target=i686-pc-none-elf -march=i686 -fno-builtin -ffreestanding -nostdlib -nostdinc++ -I src/include
CWARNINGS := -Werror -Wall
CSOURCES  := $(shell find src -type f -name "*.c" -not -path "src/arch/**/*")
CHEADERS  := $(shell find src/include -type f -name "*.h" -not -path "src/arch/**/*")
COBJECTS  := $(patsubst src/%.c,build/%.o,$(CSOURCES))
CDEPS     := $(patsubst build/%.o,build/%.d,$(COBJECTS))

LDFLAGS    := --target=i686-pc-none-elf -march=i686 -ffreestanding -nostdlib -L build
LDWARNINGS := -Werror -Wall

.PHONY: all clean run-qemu

all: build/kernel.iso

run-qemu: build/kernel.iso
	qemu-system-i386 -cdrom build/kernel.iso -curses

clean:
	rm -rf build/*

build/kernel.iso: build/iso/boot/grub/grub.cfg build/iso/boot/kernel.bin
	grub-mkrescue -o $@ build/iso

build/iso/boot/grub/grub.cfg: grub.cfg
	mkdir -p $(@D)
	cp $< $@

build/iso/boot/kernel.bin: build/linker.ld build/libarch.a build/libkernel.a
	$(CC) -T $< -o $@ $(LDFLAGS) $(LDWARNINGS) -larch -lkernel

build/libkernel.a: $(COBJECTS)
	$(AR) $(ARFLAGS) $@ $^

build/%.o: src/%.c
	$(CC) $(CFLAGS) $(WARNINGS) -MMD -MP -c $< -o $@

-include $(CDEPS)
include src/arch/i686/module.mk
