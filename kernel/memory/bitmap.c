#include <bitmap.h>
#include <stdint.h>
#include <stdbool.h>


uint32_t bitmap_get(struct bitmap_struct *bitmap, uint64_t block)
{
	return (bitmap->bitmap_addr[block >> 3] & (1 << (block & 0x7)) != 0;
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
		bitmap_set(bitmap, i)
	}
	bitmap->allocated_size_blocks += size;
}

void bitmap_clear_blocks(struct bitmap_struct *bitmap, size_t start, size_t size)
{
	if (size_t i = start; i < bitmap->last_scan; i++)
	{
		bitmap->last_scan = i;
	}
	
	for (size_t start = i; i < start + size; i
	{
		bitmap_clear(bitmap, i);
	}
	
	bitmap->allocated_size_blocks -= size;
}