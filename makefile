ARCH := x86_64
IMAGE_NAME := tchux-$(ARCH)
KERNEL := kernel/kernel

# QEMU
# -serial in qemu flags
QEMUFLAGS := -m 2G -monitor stdio -d int -M smm=off

# LIMINE
LIMINE_DIR := bootloader/limine
LIMINE_BRANCH := v9.x-binary 	


# OVMF 
OVMF_DIR := bootloader/ovmf
OVMF_CODE := $(OVMF_DIR)/ovmf-code-$(ARCH).fd

# XORRISO
XORRISOFLAGS := -R -r -J -hfsplus -apm-block-size 2048 \
				--efi-boot boot/limine/limine-uefi-cd.bin \
				-efi-boot-part --efi-boot-image --protective-msdos-label

# Compiler
CC := gcc
CFLAGS := -mcmodel=large -ffreestanding -O2 -Wall -Werror -Wextra -Ikernel/libc -Ikernel/include -Ikernel/core
LDFLAGS := -nostdlib -T kernel/linker.ld

# Kernel source and objects
KERNELSRC := \
	kernel/main.c \
	kernel/cpu/gdt.c \
	kernel/memory/memory.c \
	kernel/cpu/idt.c \
	kernel/cpu/ports.c \
	kernel/graphics/fb.c \
	kernel/graphics/psf.c \
	kernel/graphics/console.c \
	kernel/graphics/draw.c \
	kernel/graphics/shell.c \
	kernel/drivers/serial.c \
	kernel/cpu/sse.c \
	kernel/core/core.c
	
KERNELOBJ := $(KERNELSRC:.c=.o)

override IMAGE_NAME := tchux-$(ARCH)

.PHONY: all run clean

all: $(IMAGE_NAME).iso

# Setup ovmf
bootloader/ovmf/ovmf-code-$(ARCH).fd:
	mkdir -p bootloader/ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-code-$(ARCH).fd
	case "$(ARCH)" in \
		aarch64) dd if=/dev/zero of=$@ bs=1 count=0 seek=67108864 2>/dev/null;; \
		riscv64) dd if=/dev/zero of=$@ bs=1 count=0 seek=33554432 2>/dev/null;; \
	esac

# Setup limine
bootloader/limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=$(LIMINE_BRANCH) --depth=1 $(LIMINE_DIR)
	$(MAKE) -C $(LIMINE_DIR)

# kernel compile
$(KERNEL): $(KERNELOBJ)
	ld $(LDFLAGS) -o $@ $(KERNELOBJ)

# crete iso
$(IMAGE_NAME).iso: bootloader/limine $(KERNEL) init/boot/limine/limine.conf
	rm -rf iso_root
	mkdir -p iso_root/boot/limine iso_root/EFI/BOOT
	cp -v $(KERNEL) iso_root/boot/kernel
	cp -v init/boot/limine/limine.conf iso_root/boot/limine/
	cp -v $(LIMINE_DIR)/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v $(LIMINE_DIR)/BOOTX64.EFI iso_root/EFI/BOOT/
	xorriso -as mkisofs $(XORRISOFLAGS) iso_root -o $(IMAGE_NAME).iso
	rm -rf iso_root

run:
	run-$(ARCH)

run-x86_64: bootloader/ovmf/ovmf-code-$(ARCH).fd $(IMAGE_NAME).iso
	qemu-system-$(ARCH) -M q35 \
	-drive if=pflash,unit=0,format=raw,file=bootloader/ovmf/ovmf-code-$(ARCH).fd,readonly=on  \
	-cdrom $(IMAGE_NAME).iso $(QEMUFLAGS)

clean:
	rm -rf iso_root $(IMAGE_NAME).iso limine ovmf $(KERNEL) kernel/**/*.o
	
