#include <limine.h>
#include <core.h>

static volatile struct limine_paging_mode_request limine_paging_request = {
    .id = LIMINE_PAGING_MODE_REQUEST,
    .revision = 0,
    .mode = LIMINE_PAGING_MODE_X86_64_4LVL
};

static volatile struct limine_kernel_address_request limine_kernel_addr_request = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST, 
	.revision = 0
};

static volatile struct limine_hhdm_request limine_hhdm_request = {
    .id = LIMINE_HHDM_REQUEST, 
	.revision = 0
};

static volatile struct limine_memmap_request limine_memory_map_request = {
    .id = LIMINE_MEMMAP_REQUEST, 
	.revision = 0
};

static volatile struct limine_smp_request limine_smp_request = {
    .id = LIMINE_SMP_REQUEST, 
	.revision = 0
};

static volatile struct limine_rsdp_request limine_rsdp_req = {
    .id = LIMINE_RSDP_REQUEST, 
	.revision = 0
};
	
void init_bootinfo(void)
{
	kernel.hhdm = limine_hhdm_request.response->offset;
	kernel.memmap = limine_memory_map_request.response;
	
	kernel.memory_total = 0;
	for (int i = 0; kernel.memmap->entry_count; i++)
	{
		struct limine_memmap_entry *entry = kernel.memmap->entries[i];
		if (entry->type != LIMINE_MEMMAP_RESERVED)
		{
			kernel.memory_total += entry->length;
		}
	}
}