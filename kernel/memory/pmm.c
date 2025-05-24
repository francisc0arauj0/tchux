#include <pmm.h>
#include <bitmap.h>
#include <bootinfo.h>
#include <core.h>
#include <memory.h>

struct bitmap_struct physical;

void init_pmm()
{
	struct bitmap_struct *bitmap = &physical;
	
	bitmap->ready = false;
	
	physical.bitmap_size_blocks = (kernel.memory_total + 4096 - 1) / 4096;
	physical.bitmap_size_bytes = (physical.bitmap_size_blocks + 8 - 1) / 8;
	
	struct limine_memmap_entry *memory_map = 0;	

	for (uint64_t i = 0; i < kernel.memmap->entry_count; i++)
	{
		struct limine_memmap_entry *entry = kernel.memmap->entries[i];
		if (entry->type != LIMINE_MEMMAP_USABLE || entry->length < physical.bitmap_size_bytes)
		{
			continue;
		}
		memory_map = entry;
		break;
	}
	
	if (!memory_map)
	{
		/* panic */
		return;
	}
	
	size_t bitmap_start_phys = memory_map->base;
	
	physical.bitmap_addr = (uint8_t *)(bitmap_start_phys + kernel.hhdm);
	
	memset(physical.bitmap_addr, 0xff, physical.bitmap_size_bytes);
	
	for (uint64_t i = 0; i < kernel.memmap->entry_count; i++)
	{
		struct limine_memmap_entry *entry = kernel.memmap->entries[i];
		if (entry->type == LIMINE_MEMMAP_USABLE)
		{
			bitmap_mark_region(bitmap, (void *)entry->base, entry->length, 0);
		}
	}
	
	for (uint64_t i = 0; i < kernel.memmap->entry_count; i++)
	{
		struct limine_memmap_entry *entry = kernel.memmap->entries[i];
		if (entry->type != LIMINE_MEMMAP_USABLE)
		{
			bitmap_mark_region(bitmap, (void *)entry->base, entry->length, 1);
		}
	}
	
	bitmap_mark_region(bitmap, (void *)bitmap_start_phys, physical.bitmap_size_bytes, 1);
	physical.allocated_size_blocks = 0;
	
	bitmap->ready = true;
}