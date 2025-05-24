#include <stdint.h>
#include <limine.h>

struct kernel_struct
{
	struct limine_boot_time_response *boot_time;
	struct limine_kernel_address_response *kernel_addr; /* Physical addr and Virtual addr */
	
	uint64_t *gdt_addr;
	uint64_t *idt_addr;
	uint64_t *framebuffer_addr;
	
	uint64_t hhdm;
	struct limine_memmap_response *memmap;
	size_t memory_total;
};

extern struct kernel_struct kernel;