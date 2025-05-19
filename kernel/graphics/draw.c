#include <fb.h>
#include <draw.h>
#include <stdint.h>

void draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t i = (x + y * framebuffer.width) * 4;
	framebuffer.addr[i + 0] = b;
	framebuffer.addr[i + 1] = g;
	framebuffer.addr[i + 2] = r;
	framebuffer.addr[i + 3] = 0;
}

void draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t o = (x + y * framebuffer.width) * 4;
	
	for (int32_t i = 0; i < h; i++)
	{
		for (int32_t j = 0; j < w; j++)
		{
			framebuffer.addr[o + j * 4] = b;
			framebuffer.addr[o + j * 4 + 1] = g;
			framebuffer.addr[o + j * 4 + 2] = r;
			framebuffer.addr[o + j * 4 + 3] = 0;
		}
		o += framebuffer.pitch;
	}
}