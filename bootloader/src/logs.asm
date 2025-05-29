;============================
; File: Bootloader Logs
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Bootloader
;===========================

real_mode_log:
	db "started in 16-bit real mode", 0xa, 0xd, 0

load_kernel_log:
	db "loading kernel into memory", 0

protected_mode_log:
	db "successfully landed in 32-bit protected mode", 0

disk_error_log:
	db "disk error", 0