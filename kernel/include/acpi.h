#ifndef ACPI_H
#define ACPI_H

#include <uacpi/uacpi.h>

void init_acpi();

void *uacpi_kernel_alloc(uacpi_size size);
void uacpi_kernel_free(void *mem);

#endif