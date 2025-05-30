;============================
; File: Kernel Main ASM
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Kernel
;===========================

bits 32
global _start
extern kmain

_start:
    jmp kmain
	jmp $
