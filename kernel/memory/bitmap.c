#include <bitmap.h>
#include <stdint.h>
#include <stdbool.h>

size_t bitmap_block(struct bitmap_struct *bitmap, void *ptr)
{
	uint8_t *u8_ptr = (uint8_t *)ptr;
	return (size_t)(u8_ptr - bitmap->mem_start) / 4096;
}

size_t bitmap_block_roundup(struct bitmap_struct *bitmap, void *ptr)
{
	uint8_t *u8_ptr = (uint8_t *)ptr;
	return (size_t)(((size_t)(u8_ptr - bitmap->mem_start) + 4096 - 1) / 4096);
}

uint32_t bitmap_get(struct bitmap_struct *bitmap, uint64_t block)
{
	return (bitmap->bitmap_addr[block >> 3] & (1 << (block & 0x7))) != 0;
}

void bitmap_set(struct bitmap_struct *bitmap, uint64_t block)
{
	bitmap->bitmap_addr[block >> 3] |= 1 << (block & 0x7);
}

void bitmap_clear(struct bitmap_struct *bitmap, uint64_t block)
{
	bitmap->bitmap_addr[block >> 3] &= ~(1 << (block & 0x7));
}

void bitmap_mark_blocks(struct bitmap_struct *bitmap, size_t start, size_t size)
{
	for (size_t i = start; i < start + size; i++)
	{
		bitmap_set(bitmap, i);
	}
	bitmap->allocated_size_blocks += size;
}

void bitmap_clear_blocks(struct bitmap_struct *bitmap, size_t start, size_t size)
{
	if (start < bitmap->last_scan)
	{
		bitmap->last_scan = start;
	}
	
	for (size_t i = start; i < start + size; i++)
	{
		bitmap_clear(bitmap, i);
	}
	
	bitmap->allocated_size_blocks -= size;
}

void bitmap_mark_region(struct bitmap_struct *bitmap, void *base_ptr, size_t size_bytes, int used)
{
	size_t base;
	size_t size;
		
	if (used)
	{
		base = bitmap_block(bitmap, base_ptr);
		size = (size_bytes + 4096 - 1) / 4096;
		bitmap_mark_blocks(bitmap, base, size); 
	}
	else
	{
		base = block_roundup(bitmap, base_ptr);
		size = size_bytes / 4096;
		bitmap_clear_blocks(bitmap, base, size);
	}
}