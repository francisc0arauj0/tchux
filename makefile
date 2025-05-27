ASM = nasm
BOOTLOADER_SRC = bootloader/src
BUILD_DIR = build


$(BUILD_DIR)/main_floppy.img: $(BUILD_DIR)/bootloader.bin
	cp $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/main_floppy.img
	# dd if=/dev/zero of=$(BUILD_DIR)/main_floppy.img bs=512 count=2880
	truncate -s 1440k $(BUILD_DIR)/main_floppy.img

$(BUILD_DIR)/bootloader.bin: $(BOOTLOADER_SRC)/boot.asm
	$(ASM) $(BOOTLOADER_SRC)/boot.asm -f bin -o $(BUILD_DIR)/bootloader.bin

    
# qemu-system-i386 -m 2G -monitor stdio -d int -M smm=off -fda build/main_floppy.img 