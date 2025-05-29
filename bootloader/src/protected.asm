;============================
; File: Protected Mode Bootloader
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Bootloader
;===========================

bits 16

protected_mode_switch:
	cli
	
	; prepare GDT
	lgdt [gdt_descriptor]
	
	; enable protected mode (CR0.PE = 1)
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp code_segment:protected_mode_start

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
	