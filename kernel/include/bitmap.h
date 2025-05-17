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

#define BLOCKS_PER_BYTE 8
#define BLOCKS_SIZE 4096
#define INVALID_BLOCK ((uint64_t)-1)

uint64_t addr = block / BLOCKS_PER_BYTE;
uint64_t offset = block % BLOCKS_PER_BYTE;

uint32_t bitmap_get(struct bitmap_struct *bitmap, uint64_t block);
void bitmap_set(struct bitmap_struct *bitmap, uint64_t block, bool value);



#endif