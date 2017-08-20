OBJECTS = src/boot/boot.o src/main.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T src/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: fozenos.iso

# run emulator
run:
	qemu-system-i386 -boot d -cdrom fozenos.iso #-m 128M
debug:
	qemu-system-i386 -s -S -boot d -cdrom fozenos.iso

# iso image
fozenos.iso: kernel.elf src/iso/boot/grub/grub.cfg
	cp kernel.elf src/iso/boot/kernel.elf
	grub2-mkrescue --xorriso=/usr/local/src/xorriso-1.4.6/xorriso/xorriso \
	               -o $@ src/iso

# kernel
kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

# C code
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
# ASM code
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# clean
clean:
	rm -rf fozenos.iso kernel.elf
	rm -rf src/*.o src/*~
