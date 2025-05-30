/*
============================
 File: VGA Header
 Author: Francisco Araújo
 Year: 2025
 Project: Tchux Kernel
;===========================
*/

#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define COLOR8_BLACK 0
#define COLOR8_LIGHT_GREY 7
#define COLOR8_WHITE 15

struct vga_config_struct
{
	u16 *addr;
	u16 width;
	u16 height;
	u16 column;
	u16 line;
	u16 default_color;
	u16 current_color;
};

extern struct vga_config_struct vga_config;

void vga_init();
void vga_reset();
void vga_set_bg(u8 color, u8 fg);
void vga_new_line();
void vga_scroll_up();
void vga_print(const char *c);

#endif