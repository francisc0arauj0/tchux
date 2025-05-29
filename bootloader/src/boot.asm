;============================
; File: Bootloader
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Bootloader
;===========================

org 0x7C00

kernel_offset equ 0x1000

start:
	mov [boot_drive], dl
	mov bp, 0x9000
	mov sp, bp
	
	mov bx, real_mode_log
	call print
	
	call main
	call protected_mode_switch
	
	jmp $


%include "bootloader/src/gdt.asm"
%include "bootloader/src/print.asm"
%include "bootloader/src/logs.asm"
%include "bootloader/src/disk.asm"
%include "bootloader/src/protected.asm"

bits 16

main:
	mov bx, load_kernel_log
	call print
	
	mov bx, kernel_offset
	mov dh, 1
	mov dl, [boot_drive]
	call disk_load
	
	ret
	
bits 32

begin_protected_mode:
	call kernel_offset
	jmp $
	

boot_drive:
	db 0

times 510-($-$$) db 0
dw 0xAA55