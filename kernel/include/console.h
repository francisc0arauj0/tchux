#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

struct console_struct
{
	uint32_t width;
	uint32_t height;
	uint32_t char_width;
	uint32_t char_height;
};

extern struct console_struct console;

extern int bg_color[];
extern int text_color[];

void init_console();
void clear_screen();

void change_text_color(int r, int g, int b);
void change_bg_color(int r, int g, int b);

uint32_t get_console_x();
uint32_t get_console_y();
void set_console_x(uint32_t x);
void set_console_y(uint32_t y);

void console_putc(int c);
void console_write(char *str);

#endif