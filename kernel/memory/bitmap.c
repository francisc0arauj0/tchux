#include <bitmap.h>
#include <stdint.h>
#include <stdbool.h>

void *bitmap_to_ptr(struct bitmap_struct *bitmap, size_t block)
{
	uint8_t *u8_ptr = (uint8_t *)(bitmap->mem_start + (block * 4096));
	return (void *)(u8_ptr);
}

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
		base = bitmap_block_roundup(bitmap, base_ptr);
		size = size_bytes / 4096;
		bitmap_clear_blocks(bitmap, base, size);
	}
}

size_t bitmap_find_free_region(struct bitmap_struct *bitmap, size_t blocks)
{
	size_t current_region_start = bitmap->last_scan;
	size_t current_region_size = 0;
	
	for (size_t i = current_region_start; i < bitmap->bitmap_size_blocks; i++)
	{
		if (bitmap_get(bitmap, i))
		{
			current_region_size = 0;
			current_region_start = i + 1;
		}
		else
		{
			if (blocks == 1)
			{
				bitmap->last_scan = current_region_start + 1;
			}
			
			current_region_size++;
			
			if (current_region_size >= blocks)
			{
				return current_region_start;
			}
		}
	}
	
	return ((size_t)-1);
}

void *bitmap_allocate(struct bitmap_struct *bitmap, size_t blocks)
{
	if (blocks == 0)
	{
		return 0;
	}
	
	size_t picked_region = bitmap_find_free_region(bitmap, blocks);
	
	if (picked_region == (size_t)-1)
	{
		return 0;
	}
	
	bitmap_mark_blocks(bitmap, picked_region, blocks);
	return bitmap_to_ptr(bitmap, picked_region);
}