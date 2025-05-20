#include <idt.h>
#include <gdt.h>
#include <core.h>

struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

void init_idt()
{
	idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
	idt_ptr.base = (uint64_t) &idt_entries;

	asm volatile("lidt %0" ::"m"(idt_ptr) : "memory");
	kernel.idt_addr = (void*)idt_ptr.base;
}

void set_idt(uint8_t id, uint64_t handler, uint8_t flags)
{
	idt_entries[id].base_low = (uint16_t)handler;
	idt_entries[id].ss = GDT_KERNEL_CODE;
	idt_entries[id].ist = 0;
	idt_entries[id].reserved = 0;
	idt_entries[id].flags = flags;
	idt_entries[id].base_mid = (uint16_t)(handler >> 16);
	idt_entries[id].base_high = (uint32_t)(handler >> 32);
}