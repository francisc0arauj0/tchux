;============================
; File: Disk
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Bootloader
;===========================


disk_load:
	pusha
	
	push dx
	
	; load sector 2 (LBA 1) to 0x1000
	mov ah, 0x02 ; read sectors
	mov al, dh ; number of sectors to read
	mov ch, 0 ; cylinder 0
	mov cl, 2 ; sctor 2
	mov dh, 0 ; header 0

	int 0x13 ; call BIOS to read from disk
	
	pop dx
	
	; Check carry flag.
	jc disk_error
	
	; check that the expected number of sectors were read.
	cmp al, dh
	jne disk_error
	
	popa
	ret

disk_error:
	mov bx, disk_error_log
	call print
	jmp $
