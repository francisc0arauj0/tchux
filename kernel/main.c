#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <gdt.h>
#include <idt.h>
#include <fb.h>
#include <console.h>
#include <serial.h>
#include <sse.h>
#include <shell.h>
#include <bootinfo.h>

static void hcf(void)
{
	for(;;)
	{
		asm volatile("hlt");
	}
}

static volatile LIMINE_BASE_REVISION(3);
void kmain(void)
{	
	if (LIMINE_BASE_REVISION_SUPPORTED == false)
	{
		hcf();
	}
	
	init_sse();
	init_serial();
	
	/* limine */
	init_bootinfo();
	
	/* framebuffer */
	init_fb();
	init_console();
	init_shell(1);
	
	/* cpu */
	init_gdt();
	init_idt();
	
	hcf();
}