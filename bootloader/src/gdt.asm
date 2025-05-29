;============================
; File: Global Descriptor Table (GDT)
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Bootloader
;===========================

gdt_start:

gdt_null:
	dd 0
	dd 0

gdt_code:
	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0

gdt_data:
	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

code_segment equ gdt_code - gdt_start
data_segment equ gdt_data - gdt_start