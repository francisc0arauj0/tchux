ASM = nasm
CC = gcc
LD = ld

CC_FLAGS = -m32 -ffreestanding -fno-pic
LD_FLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary

BOOTLOADER_SRC = bootloader/src
KERNEL_SRC = kernel

BUILD_DIR = build

all: main_floppy

bootloader_build:
	$(ASM) $(BOOTLOADER_SRC)/boot.asm -o $(BUILD_DIR)/bootloader.bin

kernel_build:
	$(ASM) -f elf $(KERNEL_SRC)/main.asm -o $(BUILD_DIR)/main_asm.o
	$(CC) $(CC_FLAGS) -c $(KERNEL_SRC)/main.c -o $(BUILD_DIR)/main.o
	$(LD) $(LD_FLAGS) -o $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/main_asm.o $(BUILD_DIR)/main.o

main_floppy: bootloader_build kernel_build
	dd if=/dev/zero of=build/main_floppy.img bs=512 count=2880
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$(BUILD_DIR)/main_floppy.img bs=512 seek=1 conv=notrunc
	



 
#$(BUILD_DIR)/main_floppy.img: $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/kernel.bin
#	dd if=/dev/zero of=build/main_floppy.img bs=512 count=2880
#	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
#	dd if=$(BUILD_DIR)/kernel.bin of=$(BUILD_DIR)/main_floppy.img bs=512 seek=1 conv=notrunc

#$(BUILD_DIR)/bootloader.bin: $(BOOTLOADER_SRC)/boot.asm $(BOOTLOADER_SRC)/gdt.asm
#	$(ASM) $< -f bin -o $@
#
#$(BUILD_DIR)/kernel.bin: $(KERNEL_SRC)/kernel.asm
#	$(ASM) $< -f bin -o $@
#
    
# qemu-system-i386 -m 2G -monitor stdio -d int -M smm=off -fda build/main_floppy.img -boot a