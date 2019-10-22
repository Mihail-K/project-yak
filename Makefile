ARFLAGS := rcs

ASM := nasm
ASMFLAGS := -felf32

CC := clang
CFLAGS := --target=i686-pc-none-elf -march=i686 -fno-builtin -ffreestanding -nostdlib -nostdinc++ -I src/include
CWARNINGS := -Werror -Wall

LD := ld
LDFLAGS := --target=i686-pc-none-elf -march=i686 -ffreestanding -nostdlib -L build
LDWARNINGS := -Werror -Wall

.PHONY: all clean

all: build/kernel.iso

clean:
	rm -r build/*

build/kernel.iso: build/iso/boot/grub/grub.cfg build/iso/boot/kernel.bin
	grub-mkrescue -o $@ build/iso

build/iso/boot/grub/grub.cfg: grub.cfg
	mkdir -p $(@D)
	cp $< $@

build/iso/boot/kernel.bin: build/linker.ld build/libarch.a
	$(CC) -T $< -o $@ $(LDFLAGS) $(LDWARNINGS) -larch

include src/arch/i686/module.mk
