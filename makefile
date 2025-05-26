ASM = nasm
BUILD_DIR = build

$(BUILD_DIR)/main_floppy.img: $(BUILD_DIR)/main.bin
	cp $(BUILD_DIR)/main.bin $(BUILD_DIR)/main_floppy.img
	truncate -s 1440k $(BUILD_DIR)/main_floppy.img

$(BUILD_DIR)/main.bin: bootloader/boot.asm
	mkdir -p $(BUILD_DIR)
	$(ASM) bootloader/boot.asm -f bin -o $(BUILD_DIR)/main.bin
	
	
# qemu-system-i386 -fda build/main_floppy.img