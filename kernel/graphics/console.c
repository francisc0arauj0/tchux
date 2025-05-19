#include <console.h>
#include <stdint.h>
#include <psf.h>
#include <console.h>
#include <draw.h>

uint32_t width = 0;
uint32_t height = 0;

void init_console()
{
	width = 0;
	height = 0;
	
	draw_rect(20, 20, 50, 50, 255, 0, 0);
	draw_rect(120, 20, 50, 50, 0, 255, 0);
	draw_rect(220, 20, 50, 50, 0, 0, 255);
	load_default_font();
	psf_putc(300, 300, 'a', 255, 0, 0);
	psf_write(500, 500, "Hello World", 255, 0, 0);
}
	
uint32_t get_console_x()
{
	return width;
}

uint32_t get_console_y() 
{
	return height;
}