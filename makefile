ARCH := x86_64
QEMUFLAGS := -m 2G -monitor stdio -d int -M smm=off
XORRISOFLAGS := -R -r -J -hfsplus -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label
CC := gcc
CFLAGS := -mcmodel=large -ffreestanding -O2 -Wall -Werror -Wextra -Ikernel/libc -Ikernel/include -Ikernel/core
LDFLAGS := -nostdlib -T kernel/linker.ld
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
	kernel/drivers/serial.c \
	kernel/cpu/sse.c \
	kernel/core/core.c
KERNELOBJ := $(KERNELSRC:.c=.o)
KERNEL := kernel/kernel

override IMAGE_NAME := tchux-$(ARCH)

.PHONY: all run clean

all: $(IMAGE_NAME).iso

# setup ovmf
bootloader/ovmf/ovmf-code-$(ARCH).fd:
	mkdir -p bootloader/ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-code-$(ARCH).fd
	case "$(ARCH)" in \
		aarch64) dd if=/dev/zero of=$@ bs=1 count=0 seek=67108864 2>/dev/null;; \
		riscv64) dd if=/dev/zero of=$@ bs=1 count=0 seek=33554432 2>/dev/null;; \
	esac

# setup limine
bootloader/limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1 bootloader/limine
	$(MAKE) -C bootloader/limine

# kernel compile
$(KERNEL): $(KERNELOBJ)
	ld $(LDFLAGS) -o $@ $(KERNELOBJ)

# crete iso
$(IMAGE_NAME).iso: bootloader/limine $(KERNEL) init/boot/limine/limine.conf
	rm -rf iso_root
	mkdir -p iso_root/boot/limine iso_root/EFI/BOOT
	cp -v $(KERNEL) iso_root/boot/kernel
	cp -v init/boot/limine/limine.conf iso_root/boot/limine/
	cp -v bootloader/limine/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v bootloader/limine/BOOTX64.EFI iso_root/EFI/BOOT/
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
	
	
# -serial in qemu flags
