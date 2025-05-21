#ifndef IOPIC_H
#define IOPIC_H

#include <stdint.h>
#include <stdbool.h>

struct iopic_struct
{
	struct iopic_struct *next;
	uint8_t id;
	uint64_t phys;
	uint64_t virt;
	int ioapic_red_start;
	int ioapic_red_end;
}

extern struct iopic_struct *iopic;


uint32_t ioapic_read(uint64_t virt, uint32_t reg);
void ioapic_write(uint64_t virt, uint32_t reg, uint32_t value);


#endif