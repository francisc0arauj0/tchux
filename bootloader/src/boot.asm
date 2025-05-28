org 0x7C00

kernel_offset equ 0x1000

start:
	mov [boot_drive], dl
	mov bp, 0x9000
	mov sp, bp
	jmp main


%include "bootloader/src/gdt.asm"

bits 16

main:
	; this causes the stack to stay in 0x0000:0x7C00
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00

	; load sector 2 (LBA 1) to 0x1000
	mov ah, 0x02			; read sectors
	mov al, 1				; number of sectors to read
	mov ch, 0				; cylinder 0
	mov cl, 2				; sctor 2
	mov dh, 0				; header 0
	mov dl, [boot_drive]	; drive
	mov bx, kernel_offset	; destination address
	int 0x13				; call BIOS to read from disk
	
	jc disk_error			; if CF is set, error
	
	cli						; disable interrupts
	
	; prepare GDT
	lgdt [gdt_descriptor]
	
	; enable protected mode (CR0.PE = 1)
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	; jump to protected mode 
	jmp code_segment:protected_mode_start 
	
disk_error:
	hlt
	jmp $

boot_drive:
	db 0


bits 32

protected_mode_start:
	mov ax, data_segment
	
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000
	mov esp, ebp
	
	call begin_protected_mode

begin_protected_mode:
	call kernel_offset
	jmp $
	
code_segment equ gdt_code - gdt_start
data_segment equ gdt_data - gdt_start

times 510-($-$$) db 0
dw 0xAA55