org 0x7C00
bits 16

start:
	jmp main
	
puts:
	; save regs we will modify
	push si
	push ax

.loop:
	lodsb			; load next char in al
	or al, al		; verify if next char is null?
	jz .done
	
	mov ah, 0x0e	; call bios interrupt
	mov bh, 0		; page number 0
	int 0x10		; bios video interrupt
	
	jmp .loop
	
.done:
	pop ax
	pop si
	ret

main:
	; setup data segments
	mov ax, 0
	mov ds, ax
	mov es, ax
	
	; setup stack
	mov ss, ax
	mov sp, 0x7C00	; stack grows from where we are loaded in memory
	
	mov si, msg
	call puts
	
	hlt
	
.halt:
	jmp .halt
	

msg: 
	db 'Bootloader working', 0
	
times 510-($-$$) db 0
dw 0AA55h