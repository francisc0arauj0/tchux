ARCH = x86_64

CC = gcc
CC_FLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-pic -fno-pie -Ikernel/include/  -Ikernel/include/libc

LD = ld
LD_FLAGS = -nostdlib -T kernel/linker.ld

XORRISO = xorriso
XORRISO_FLAGS = -R -r -J -hfsplus -apm-block-size 2048 --efi-boot limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label

QEMU = qemu-system-$(ARCH)
QEMU_FLAGS =  -M q35 -m 2G -monitor stdio -d int -M smm=off

override IMAGE_NAME := tchux-$(ARCH)

.PHONY: all run clean

all: $(IMAGE_NAME).iso

# setup limine
limine:
	$(MAKE) -C limine

# kernel compile
tchux_kernel: $(KERNEL_SRC)
	mkdir -p out
	$(CC) $(CC_FLAGS) -c kernel/main.c -o out/main.o
	$(CC) $(CC_FLAGS) -c kernel/cpu/gdt.c -o out/gdt.o
	$(LD) $(LD_FLAGS) -o $@ out/main.o out/gdt.o

# crete iso
$(IMAGE_NAME).iso: limine tchux_kernel init/limine.conf
	mkdir -p iso_root/limine iso_root/EFI/BOOT
	cp -v tchux_kernel iso_root/kernel
	cp -v init/limine.conf iso_root/limine/
	cp -v limine/limine-uefi-cd.bin iso_root/limine/
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT
	$(XORRISO) -as mkisofs $(XORRISO_FLAGS) iso_root -o $(IMAGE_NAME).iso
	rm -rf iso_root
	rm tchux_kernel
	rm -rf out


run: ovmf-code-$(ARCH).fd $(IMAGE_NAME).iso
	$(QEMU) $(QEMU_FLAGS) -drive if=pflash,unit=0,format=raw,file=ovmf-code-$(ARCH).fd,readonly=on -cdrom $(IMAGE_NAME).iso