#include <console.h>
#include <stdint.h>
#include <psf.h>
#include <console.h>
#include <draw.h>
#include <fb.h>

struct console_struct console;

int bg_color[] = {0, 0, 0};
int text_color[] = {255, 255, 255};

#define CHAR_HEIGHT (psf->charsize)
#define CHAR_WIDTH (8)

void init_console()
{
	console.width = 200;
	console.height = 200;
	
	load_default_font();
}

void clear_screen()
{
	console.width = 0;
	console.height = 0;
	draw_rect(0, 0, framebuffer.width, framebuffer.height, bg_color[0], bg_color[0], bg_color[0]);
}

void change_text_color(int r, int g, int b)
{
	text_color[0] = r;
	text_color[1] = g;
	text_color[2] = b;
}

void change_bg_color(int r, int g, int b)
{
	bg_color[0] = r;
	bg_color[1] = g;
	bg_color[2] = b;
}

uint32_t get_console_x()
{
	return console.width;
}

uint32_t get_console_y()
{
	return console.height;
}

void set_console_x(uint32_t x)
{
	console.width = x;
}

void set_console_y(uint32_t y)
{
	console.height = y;
}

void console_putc(int c)
{
	if (console.width > (framebuffer.width - CHAR_WIDTH))
	{
		console.width = 0;
		console.height += CHAR_HEIGHT;
	}
	
	switch (c)
	{
		case -1:
			draw_rect(console.width, console.height, CHAR_WIDTH, CHAR_WIDTH, bg_color[0], bg_color[1], bg_color[2]);
			console.width += CHAR_WIDTH;
			break;
		case '\n':
			console.width = 0;
			console.height += CHAR_HEIGHT;
			break;
		default:
			psf_putc(console.width, console.height, c, text_color[0], text_color[1], text_color[2]);
			console.width += CHAR_WIDTH;
			break;
	}
}

void console_write(char *str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		console_putc(str[i]);
	}
}