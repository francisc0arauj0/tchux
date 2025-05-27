org 0x7C00
bits 16

start:
	jmp main

main:
	; this causes the stack to stay in _0x0000:0x7C00
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00

	; load sector 2 (LBA 1) to 0x1000
	; mov ah, 0x02			; read sectors
	; mov al, 1				; number of sectors to read
	; mov ch, 0				; cylinder 0
	; mov cl, 2				; sctor 2
	; mov dh, 0				; header 0
	; mov dl, [boot_drive]	; drive
	; mov bx, 0x1000			; destination address
	; int 0x13				; call BIOS to read from disk
	
	; jc disk_error			; if CF is set, error
	
	; jmp 0x0000:0x1000		; jump to the loaded "kernel"
	hlt
	
;disk_error:
;	hlt
;	jmp $

;boot_drive:
;	db 0
	
.halt:
	jmp .halt
	
times 510-($-$$) db 0
dw 0xAA55