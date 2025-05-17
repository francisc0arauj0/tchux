#include <bitmap.h>
#include <stdint.h>
#include <stdbool.h>


uint32_t bitmap_get(struct bitmap_struct *bitmap, uint64_t block)
{
	uint64_t addr = block / BLOCKS_PER_BYTE;
	uint64_t offset = block % BLOCKS_PER_BYTE;
	return (bitmap->bitmap_addr[addr] & (1 << offset)) != 0;
}

void bitmap_set(struct bitmap_struct *bitmap, uint64_t block, bool value)
{
	uint64_t addr = block / BLOCKS_PER_BYTE;
	uint64_t offset = block % BLOCKS_PER_BYTE;
	if (value)
	{
		bitmap->bitmap_addr[addr] |= (1 << offset);
	} 
	else
	{
		bitmap->bitmap_addr[addr] &= ~(1 << offset);
	}
}