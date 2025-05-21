#ifndef LAPIC_H
#define LAPIC_H

#include <stdint.h>
#include <stdbool.h>

struct lapic_struct
{
	uint64_t phys;
	uint64_t virt;
}

extern struct lapic_struct lapic;

#endif