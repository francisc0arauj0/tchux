#ifndef LAPIC_H
#define LAPIC_H

#include <stdint.h>
#include <stdbool.h>

#define IA32_LAPIC_BASE_MSR 0x1B
#define IA32_LAPIC_BASE_MSR_ENABLE 0x800
#define IA32_LAPIC_BASE_MSR_BSP 0x100

struct lapic_struct
{
	uint64_t phys;
	uint64_t virt;
}

extern struct lapic_struct lapic;

bool lapic_check();
void lapic_write(uint32_t offset, uint32_t value);
uint32_t lapic_read(uint32_t offset);


size_t lapic_get_base();
void lapic_set_base(size_t lapic);

#endif