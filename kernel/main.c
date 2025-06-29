#include <gdt.h>

void kmain()
{
	gdt_init();
	
	for (;;)
	{
		asm volatile ("hlt");
	}
}