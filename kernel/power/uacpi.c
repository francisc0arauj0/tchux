#include <stdint.h>
#include <uacpi/uacpi.h>
#include <malloc.h>

void init_acpi()
{
}

/* malloc */

void *uacpi_kernel_alloc(uacpi_size size)
{
	return kr_malloc(size);
}

void uacpi_kernel_free(void *mem)
{
	kr_free(mem);
}