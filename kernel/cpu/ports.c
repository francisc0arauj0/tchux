#include <ports.h>
#include <stdint.h>

void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
	asm volatile("cpuid \n" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(*eax) : "memory");
}

uint8_t inportb(uint16_t port)
{
	char rv;
	asm volatile("inb %1, %0": "=a"(rv): "dN"(port));
	return rv;
}

void outportb(uint16_t port, uint8_t value)
{
	asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

uint16_t inportw(uint16_t port)
{
	uint16_t result;
	asm("in %%dx, %%ax" : "=a"(result) : "d"(port));
	return result;
}

void outportw(unsigned short port, unsigned short data) {
  asm("out %%ax, %%dx" : : "a"(data), "d"(port));
}

uint32_t inportl(uint32_t port)
{
	uint32_t ret;
	asm volatile("inl %%dx, %%eax" : "=a"(ret) : "d"(port));
	return ret;
}

void outportl(uint16_t port, uint32_t value) {
  asm volatile("outl %%eax, %%dx" : : "d"(port), "a"(value));
}

uint64_t rdmsr(uint32_t msrid)
{
	uint32_t low;
	uint32_t high;
	asm volatile("rdmsr" : "=a"(low), "=d"(high) : "c"(msrid));
	return (uint64_t)low << 0 | (uint64_t)high << 32;
}

uint64_t wrmsr(uint32_t msrid, uint64_t value)
{
	uint32_t low = value >> 0 & 0xFFFFFFFF;
	uint32_t high = value >> 32 & 0xFFFFFFFF;
	asm volatile("wrmsr" : : "a"(low), "d"(high), "c"(msrid) : "memory");
	return value;
}