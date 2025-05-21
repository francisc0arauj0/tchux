#include <ports.h>
#include <stdint.h>

void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
	asm volatile ("cpuid \n" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(*eax) : "memory");
}

void outportb(uint16_t port, uint8_t value)
{
	asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

char inportb(uint16_t port)
{
	char rv;
	asm volatile ("inb %1, %0": "=a"(rv): "dN"(port));
	return rv;
}