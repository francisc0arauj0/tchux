ARCH = x86_64

QEMU = qemu-system-$(ARCH)
QEMU_FLAGS =  -M q35 -m 2G -monitor stdio -d int -M smm=off

XORRISO = xorriso
XORRISO_FLAGS = -R -r -J -hfsplus -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label

CC = gcc
CC_FLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-pic -fno-pie

LD = ld
LD_FLAGS = -nostdlib -T kernel/arch/$(ARCH)/linker.ld

KERNEL_SRC = kernel/arch/$(ARCH)/main.c
KERNEL_OUT = out/kernel

override IMAGE_NAME := tchux-$(ARCH)

.PHONY: all run clean

all: $(IMAGE_NAME).iso

# setup limine
limine:
	$(MAKE) -C limine

# kernel compile
$(KERNEL_OUT): $(KERNEL_SRC)
	mkdir -p out
	$(CC) $(CC_FLAGS) -c -o out/main.o $(KERNEL_SRC)
	$(LD) $(LD_FLAGS) -o $@ out/main.o

# crete iso
$(IMAGE_NAME).iso: limine $(KERNEL_OUT) limine.conf
	rm -rf iso_root
	mkdir -p iso_root/boot/limine iso_root/EFI/BOOT
	cp -v $(KERNEL_OUT) iso_root/boot/kernel
	cp -v limine.conf iso_root/boot/limine/
	cp -v limine/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	$(XORRISO) -as mkisofs $(XORRISO_FLAGS) iso_root -o $(IMAGE_NAME).iso
	rm -rf iso_root


run-x86_64: ovmf-code-$(ARCH).fd $(IMAGE_NAME).iso
	$(QEMU) $(QEMU_FLAGS) -drive if=pflash,unit=0,format=raw,file=ovmf-code-$(ARCH).fd,readonly=on -cdrom $(IMAGE_NAME).iso

clean:
	rm -rf iso_root $(IMAGE_NAME).iso limine ovmf $(KERNELOUT) kernel/*.o