#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

/* Ports */
uint8_t inportb(uint16_t port);
void outportb(uint16_t port, uint8_t value);

uint16_t inportw(uint16_t port);
void outportw(unsigned short port, unsigned short data);

uint32_t inportl(uint32_t port);
void outportl(uint16_t port, uint32_t value);

/* CPU */
void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

/* msr */
uint64_t rdmsr(uint32_t msrid);
uint64_t wrmsr(uint32_t msrid, uint64_t value);

#endif