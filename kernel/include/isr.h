#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct interrupt_registers_struct
{
	uint64_t ds;
	
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	
	uint64_t rbp;
	uint64_t rdi;
	uint64_t rsi;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;
	
	uint64_t interrupt;
	uint64_t error;
	
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t usermode_rsp;
	uint64_t usermode_ss;
};

void init_isr();
void isr_handler(struct interrupt_registers_struct *regs);
void irq_install_handler (int irq, void (*handler)(struct interrupt_registers_struct *r));
void irq_uninstall_handler (int irq);
void irq_handler(struct interrupt_registers_struct *regs);
void disable_pic();
void remap_pic();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isr128();
extern void isr177();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif
