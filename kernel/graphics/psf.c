#include <psf.h>
#include <stdint.h>
#include <stdbool.h>
#include <gohufont.h>

struct psf1_header_struct psf1_header;
struct psf_font_struct psf_font;
struct psf1_header_struct *psf;

void load_psf(void *buffer)
{
	psf1_header = *(struct psf1_header_struct *)buffer;
	psf = (struct psf1_header_struct *)buffer;
	
	psf_font.magic = psf1_header.magic;
	psf_font.version = 1;
	psf_font.headersize = sizeof(struct psf1_header_struct);
	psf_font.flags = (psf1_header.mode == 1) ? 1 : 0;
	psf_font.numglyph = (psf1_header.mode & 0x01) ? 512 : 256;
	psf_font.bytesperglyph = psf1_header.charsize;
	psf_font.height = psf1_header.charsize;
	psf_font.width = 8;
}

void load_default_font()
{
	load_psf(&psf_gohufont[0]);
}