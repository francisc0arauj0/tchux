#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

/* Ports */
void outportb(uint16_t port, uint8_t value);
char inportb(uint16_t port);

/* CPU */
void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

/* msr */
uint64_t rdmsr(uint32_t msrid);
uint64_t wrmsr(uint32_t msrid, uint64_t value);

#endif