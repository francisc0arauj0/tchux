OUTPUT_FORMAT(elf64-x86-64)
ENTRY(kmain)

SECTIONS
{
	. =  0xffffffff80000000;
	
	.text   : {*(.text)}
	.rodata : {*(.rodata)}
	.data   : {*(.data)}
	.bss    : {*(.bss) *(COMMON)}
}