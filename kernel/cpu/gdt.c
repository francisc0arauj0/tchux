#include <gdt.h>

struct gdt_entry_struct gdt_entries[7];
struct gdt_ptr_struct gdt_ptr;

void gdt_init()
{
	gdt_ptr.limit = sizeof(struct gdt_entry_struct) * 7 - 1;
	gdt_ptr.base = (u64)&gdt_entries;
	
	/* 
	Access Byte (8 bits):
		Bit 7: P -> Present
		Bit 6: DPL (Privilege level)
		Bit 5: DPL (Privilege level)
		Bit 4: S -> Descriptior type (1 = code/data, 0 = system)
		Bit 3: E -> Executable (1 = code, 0 = data)
		Bit 2: DC -> Direction (1 = data) / Conforming ( 0 = code)
		Bit 1: RW -> Readable ( 1 = code) / Writable ( 0 = data)
		Bit 0: A -> Accessed (CPU set)
	*/
	
	/* 
	Flags Byte (7 to 4):
		Bit 7: G -> Granulary (0 = byte limit, 1 = page limit 4KiB)
		Bit 6: D/B -> Size (0 = 16-bit, 1 = 32-bit)
		Bit 5: L -> Long mode (1 = 64-bit segment, 0 = no)
		Bit 4: AVL -> Available for software (only used by software, CPU ignore)
	*/
	
	// Null Segment
	set_gdt_gate(0, 0, 0, 0, 0);
		
	// Kernel code and data (ring 0)
	set_gdt_gate(1, 0, 0, 0b10011010, 0b10100000);
	set_gdt_gate(2, 0, 0, 0b10010010, 0b11000000);
	
	// User code and data (ring 3)
	set_gdt_gate(3, 0, 0, 0b11111010, 0b10100000);
	set_gdt_gate(4, 0, 0, 0b11110010, 0b11000000);

	
	gdt_flush();
}

void set_gdt_gate(u64 id, u64 base, u64 limit, u8 access, u8 flags)
{
	gdt_entries[id].base_low = base & 0xFFFF;
	gdt_entries[id].base_middle = (base >> 16) & 0xFF;
	gdt_entries[id].base_high = (base >> 24) & 0xFF;
	
	gdt_entries[id].limit = limit & 0xFFFF;
	
	gdt_entries[id].flags = (limit >> 16) & 0x0F;
	gdt_entries[id].flags |= flags & 0xF0;
	
	gdt_entries[id].access = access;
	
}

void gdt_flush(void) 
{
    asm volatile (
        "lgdt %0\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%ss\n"
        "pushq $0x08\n"
        "lea 1f(%%rip), %%rax\n"
        "pushq %%rax\n"
        "lretq\n"
        "1:\n"
        : : "m"(gdt_ptr) : "rax", "memory"
    );
}