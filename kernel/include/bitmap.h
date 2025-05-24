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
};

void *bitmap_to_ptr(struct bitmap_struct *bitmap, size_t block);
size_t bitmap_block_roundup(struct bitmap_struct *bitmap, void *ptr);
size_t block_roundup(struct bitmap_struct *bitmap, void *ptr);

uint32_t bitmap_get(struct bitmap_struct *bitmap, uint64_t block);
void bitmap_set(struct bitmap_struct *bitmap, uint64_t block);
void bitmap_clear(struct bitmap_struct *bitmap, uint64_t block);

void bitmap_mark_blocks(struct bitmap_struct *bitmap, size_t start, size_t size);
void bitmap_clear_blocks(struct bitmap_struct *bitmap, size_t start, size_t size);

void bitmap_mark_region(struct bitmap_struct *bitmap, void *base_ptr, size_t size, int used);

size_t bitmap_find_free_region(struct bitmap_struct *bitmap, size_t blocks);
void *bitmap_allocate(struct bitmap_struct *bitmap, size_t blocks);

extern struct bitmap_struct physical;

#endif