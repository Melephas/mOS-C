CC		:= clang
CC_FLAGS := -Wall -Wextra -m32 -ffreestanding -nostdlib

OBJ		:= obj
SRC		:= src
INCLUDE	:= include

OBJECTS = obj/kernel.o \
					obj/x86/loader.o \
					obj/hardware/vga.o


.PHONY: all
all: mOS-x86.iso

run: mOS-x86.iso
	(killall qemu && sleep 1) || true
	qemu-system-i386 -cdrom mOS-x86.iso

mOS-x86.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/
	cp static/grub.cfg isodir/boot/grub/
	grub-mkrescue -o mOS-x86.iso isodir
	rm -rf isodir

obj/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c -o $@ $<

kernel.bin: static/linker.ld $(OBJECTS)
	ld -melf_i386 -T $< -o $@ $(OBJECTS)

.PHONY: clean

clean:
	rm -rf obj kernel.bin mOS-x86.iso
