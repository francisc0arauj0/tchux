ASM = nasm
BOOTLOADER_SRC = bootloader/src
KERNEL_SRC = kernel
BUILD_DIR = build

 
$(BUILD_DIR)/main_floppy.img: $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/kernel.bin
	dd if=/dev/zero of=build/main_floppy.img bs=512 count=2880
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$(BUILD_DIR)/main_floppy.img bs=512 seek=1 conv=notrunc

$(BUILD_DIR)/bootloader.bin: $(BOOTLOADER_SRC)/boot.asm $(BOOTLOADER_SRC)/gdt.asm
	$(ASM) $< -f bin -o $@

$(BUILD_DIR)/kernel.bin: $(KERNEL_SRC)/kernel.asm
	$(ASM) $< -f bin -o $@

    
# qemu-system-i386 -m 2G -monitor stdio -d int -M smm=off -fda build/main_floppy.img -boot a