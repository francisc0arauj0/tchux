/*
============================
 File: VGA
 Author: Francisco Araújo
 Year: 2025
 Project: Tchux Kernel
;===========================
*/

#include <stdint.h>
#include <vga.h>

struct vga_config_struct vga_config;


void vga_init()
{
	vga_config.addr = (u16*)0xB8000;
	vga_config.width = 80;
	vga_config.height = 25;
	vga_config.column = 0;
	vga_config.line = 10;
	vga_config.default_color = (COLOR8_BLACK << 8) | (COLOR8_WHITE << 12);
	vga_config.current_color = vga_config.default_color;
}


void vga_reset()
{
	vga_config.line = 0;
    vga_config.column = 0;
    vga_config.current_color = vga_config.default_color;
	
	for (u16 y = 0; y < vga_config.height; y++)
	{
		for (u16 x = 0; x < vga_config.width; x++)
		{
			vga_config.addr[y * vga_config.width + x] = ' ' | vga_config.default_color;
		}
	}
}

void vga_set_bg(u8 color, u8 fg)
{
	for (u16 y = 0; y < vga_config.height; y++)
	{
		for (u16 x = 0; x < vga_config.width; x++)
		{
			u16 index = y * vga_config.width + x;
			u16 entry = vga_config.addr[index];
			
			char character = entry & 0x00FF;
			
			u16 new_entry = character | (fg << 8) | (color << 12);
			vga_config.addr[index] = new_entry;
		}
	}
}

void vga_print(const char *c)
{
	while (*c)
	{
		switch (*c)
		{
			default:
				vga_config.addr[vga_config.line * vga_config.width + (vga_config.column++)] = *c | vga_config.current_color;
				break;
		}
		c++;
	}
}