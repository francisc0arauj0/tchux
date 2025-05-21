#include <stdint.h>
#include <uacpi/uacpi.h>
#include <uacpi/sleep.h>

void init_acpi()
{
	uacpi_status ret = uacpi_initialize(0);
	ret = uacpi_namespace_load();
	uacpi_set_interrupt_model(UACPI_INTERRUPT_MODEL_IOAPIC);
	ret = uacpi_namespace_initialize();
}