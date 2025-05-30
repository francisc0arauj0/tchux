/*
============================
 File: Kernel Main
 Author: Francisco Araújo
 Year: 2025
 Project: Tchux Kernel
===========================
*/

#include <vga.h>


void kmain()
{
	vga_init();
	vga_reset();
	vga_set_bg(COLOR8_WHITE, COLOR8_BLACK);
	vga_print("Hello World");
}