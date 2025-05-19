#include <isr.h>
#include <idt.h>
#include <ports.h>

char *exceptions[] = {
	"Division By Zero"
	"Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
	
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
};

void init_isr()
{
	set_idt( 0, (uint64_t) isr0, 0x8E);
	set_idt( 1, (uint64_t) isr1, 0x8E);
	set_idt( 2, (uint64_t) isr2, 0x8E);
	set_idt( 3, (uint64_t) isr3, 0x8E);
	set_idt( 4, (uint64_t) isr4, 0x8E);
	set_idt( 5, (uint64_t) isr5, 0x8E);
	set_idt( 6, (uint64_t) isr6, 0x8E);
	set_idt( 7, (uint64_t) isr7, 0x8E);
	set_idt( 8, (uint64_t) isr8, 0x8E);
	set_idt( 9, (uint64_t) isr9, 0x8E);
	set_idt(10, (uint64_t)isr10, 0x8E);
	set_idt(11, (uint64_t)isr11, 0x8E);
	set_idt(12, (uint64_t)isr12, 0x8E);
	set_idt(13, (uint64_t)isr13, 0x8E);
	set_idt(14, (uint64_t)isr14, 0x8E);
	set_idt(15, (uint64_t)isr15, 0x8E);
	set_idt(16, (uint64_t)isr16, 0x8E);
	set_idt(17, (uint64_t)isr17, 0x8E);
	set_idt(18, (uint64_t)isr18, 0x8E);
	set_idt(19, (uint64_t)isr19, 0x8E);
	set_idt(20, (uint64_t)isr20, 0x8E);
	set_idt(21, (uint64_t)isr21, 0x8E);
	set_idt(22, (uint64_t)isr22, 0x8E);
	set_idt(23, (uint64_t)isr23, 0x8E);
	set_idt(24, (uint64_t)isr24, 0x8E);
	set_idt(25, (uint64_t)isr25, 0x8E);
	set_idt(26, (uint64_t)isr26, 0x8E);
	set_idt(27, (uint64_t)isr27, 0x8E);
	set_idt(28, (uint64_t)isr28, 0x8E);
	set_idt(29, (uint64_t)isr29, 0x8E);
	set_idt(30, (uint64_t)isr30, 0x8E);
	set_idt(31, (uint64_t)isr31, 0x8E);
	
	set_idt(32, (uint64_t) irq0, 0x8E);
	set_idt(33, (uint64_t) irq1, 0x8E);
	set_idt(34, (uint64_t) irq2, 0x8E);
	set_idt(35, (uint64_t) irq3, 0x8E);
	set_idt(36, (uint64_t) irq4, 0x8E);
	set_idt(37, (uint64_t) irq5, 0x8E);
	set_idt(38, (uint64_t) irq6, 0x8E);
	set_idt(39, (uint64_t) irq7, 0x8E);
	set_idt(40, (uint64_t) irq8, 0x8E);
	set_idt(41, (uint64_t) irq9, 0x8E);
	set_idt(42, (uint64_t)irq10, 0x8E);
	set_idt(43, (uint64_t)irq11, 0x8E);
	set_idt(44, (uint64_t)irq12, 0x8E);
	set_idt(45, (uint64_t)irq13, 0x8E);
	set_idt(46, (uint64_t)irq14, 0x8E);
	set_idt(47, (uint64_t)irq15, 0x8E);
	
	set_idt(128, (uint64_t)isr128, 0x8E);
	set_idt(177, (uint64_t)isr177, 0x8E);
}

void isr_handler(struct interrupt_registers_struct *regs)
{
	if (regs->interrupt < 32)
	{
		/* panic System Halted */
		for (;;);
	}
}

void *irq_routines[16] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

void disable_pic()
{
	outportb(0x21, 0xFF);
	outportb(0xA1, 0xFF);
}

void remap_pic()
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x00);
	outportb(0xA1, 0x00);
	disable_pic();
}

void irq_install_handler (int irq, void (*handler)(struct interrupt_registers_struct *r))
{
	irq_routines[irq] = handler;
}

void irq_uninstall_handler (int irq)
{
	irq_routines[irq] = 0;
}

void irq_handler(struct interrupt_registers_struct *regs)
{
	void (*handler)(struct interrupt_registers_struct *regs);
	
	handler = irq_routines[regs->interrupt - 32];
	
	if (handler)
	{
		handler(regs);
	}
	
	if (regs->interrupt >= 40)
	{
		outportb(0xA0, 0x20);
	}
	
	outportb(0x20, 0x20);
}