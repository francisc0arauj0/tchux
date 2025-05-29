;============================
; File: Print
; Author: Francisco Araújo
; Year: 2025
; Project: Tchux Bootloader
;===========================

print:
  pusha
  mov ah, 0xe
  jmp read_character

read_character:
  mov al, [bx]

  cmp al, 0
  jne print_character
  popa
  ret

print_character:
  int 0x10
  add bx, 1
  jmp read_character