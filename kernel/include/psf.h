#ifndef PSF_H
#define PSF_H

#include <stdint.h>
#include <stdbool.h>

#define PSF1_FONT_MAGIC 0x0436

struct psf1_header_struct {
    uint16_t magic;
    uint8_t mode;
    uint8_t charsize;
};

extern struct psf1_header_struct *psf;

void load_psf(void *buffer);
void load_default_font();

void psf_putc(int x, int y, char c, uint8_t r, uint8_t g, uint8_t b);
void psf_write(int x, int y, char *str, uint8_t r, uint8_t g, uint8_t b);

#endif