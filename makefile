ASM = nasm
CC = gcc
LD = ld

CC_FLAGS = -m32 -ffreestanding -fno-pic -Ikernel/includes -Ikernel/libc
LD_FLAGS = -m elf_i386 -T linker.ld --oformat binary

BOOTLOADER_SRC = bootloader/src
KERNEL_SRC = kernel

BUILD_DIR = build

all: main_floppy

bootloader_build:
	$(ASM) $(BOOTLOADER_SRC)/boot.asm -o $(BUILD_DIR)/bootloader.bin

kernel_build:
	$(ASM) -f elf $(KERNEL_SRC)/main.asm -o $(BUILD_DIR)/main_asm.o
	$(CC) $(CC_FLAGS) -c $(KERNEL_SRC)/main.c -o $(BUILD_DIR)/main.o
	$(CC) $(CC_FLAGS) -c $(KERNEL_SRC)/drivers/vga.c -o $(BUILD_DIR)/vga.o
	$(LD) $(LD_FLAGS) -o $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/main_asm.o $(BUILD_DIR)/main.o $(BUILD_DIR)/vga.o

main_floppy: bootloader_build kernel_build
	dd if=/dev/zero of=build/main_floppy.img bs=512 count=2880
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$(BUILD_DIR)/main_floppy.img bs=512 seek=1 conv=notrunc