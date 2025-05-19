#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

void draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
void draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);

#endif