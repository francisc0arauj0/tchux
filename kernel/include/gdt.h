#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_entry_struct
{
	u16 limit;
	u16 base_low;
	u8 base_middle;
	u8 access;
	u8 flags;
	u8 base_high;
}__attribute__((packed));

struct gdt_ptr_struct
{
	u16 limit;
	u64 base;
}__attribute__((packed));

void gdt_init();
void set_gdt_gate(u64 id, u64 base, u64 limit, u8 access, u8 flags);
void gdt_flush();

#endif