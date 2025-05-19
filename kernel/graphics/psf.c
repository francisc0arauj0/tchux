#include <psf.h>
#include <stdint.h>
#include <stdbool.h>
#include <gohufont.h>
#include <draw.h>

struct psf1_header_struct *psf;


void load_psf(void *buffer)
{
	psf = (struct psf1_header_struct *)buffer;
}

void load_default_font()
{
	load_psf(&psf_gohufont[0]);
}

void psf_putc(int x, int y, char c, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t *targ = (uint8_t *)((size_t)psf + sizeof(struct psf1_header_struct) + c * psf->charsize);
	
	for (int i = 0; i < psf->charsize; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (targ[i] & (1 << (7 - j)))
			{
				draw_pixel(x + j, y + i, r, g, b);
			}
		}
	}
}