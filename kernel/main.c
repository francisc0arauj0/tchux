/*
============================
 File: Kernel Main
 Author: Francisco Araújo
 Year: 2025
 Project: Tchux Kernel
===========================
*/

void kmain()
{
	char *vm = (char *) 0xb8000;
	*vm = 'X';
}