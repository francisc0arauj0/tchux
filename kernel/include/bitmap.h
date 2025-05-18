#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdbool.h>

struct bitmap_struct
{
	uint8_t *bitmap_addr;
	uint64_t bitmap_size_blocks;
	uint64_t bitmap_size_bytes;
	uint64_t allocated_size_blocks;
	uint64_t last_scan;
	uint64_t mem_start;
	bool ready;
}

uint32_t bitmap_get(struct bitmap_struct *bitmap, uint64_t block)
void bitmap_set(struct bitmap_struct *bitmap, uint64_t block)
void bitmap_clear(struct bitmap_struct *bitmap, uint64_t block)

void bitmap_mark_blocks(struct bitmap_struct *bitmap, size_t start, size_t size);
void bitmap_clear_blocks(struct bitmap_struct *bitmap, size_t start, size_t size);



#endif