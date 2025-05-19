#include <shell.h>
#include <console.h>

void init_shell(int id)
{
	if (id < 0)
	{
		return;
	};

	shell_welcome_message();
	console_write(SHELL_PROMPT);
}

void shell_welcome_message()
{
	clear_screen();
	console_write("Tchux Shell\n");
	console_write("\nWelcome to Tchux OS\n");
	console_write("Copyright (C) Francisco Araujo.\n\n");
}