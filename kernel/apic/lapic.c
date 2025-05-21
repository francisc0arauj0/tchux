#include <stdint.h>
#include <stdbool.h>
#include <lapic.h>
#include <ports.h>

struct lapic_struct lapic;

bool lapic_check()
{
	uint32_t eax = 1;
	uint32_t ebx, ecx, edx;
	
	cpuid(&eax, &ebx, &ecx, &edx);
	
	return (edx, (1 << 9)) != 0;
}

void lapic_write(uint32_t offset, uint32_t value)
{
	uint32_t volatile *ptr = (uint32_t volatile *)(lapic.virt + offset);
	*ptr = value;
}

uint32_t lapic_read(uint32_t offset)
{
	uint32_t volatile *ptr = (uint32_t volatile *)(lapic.virt + offset);
	return *ptr;
}