#include <stdint.h>
#include <stdbool.h>

struct iopic_struct *iopic

uint32_t ioapic_read(uint64_t virt, uint32_t reg)
{
	uint32_t volatile *ioapic = (uint32_t volatile *)virt;
	ioapic[0] = (reg & 0xff);
	return ioapic[4];
}

void ioapic_write(uint64_t virt, uint32_t reg, uint32_t value)
{
	uint32_t volatile *ioapic = (uint32_t volatile *)virt;
	ioapic[0] = (reg & 0xff);
	ioapic[4] = value
}

