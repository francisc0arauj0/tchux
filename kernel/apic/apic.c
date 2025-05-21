#include <stdint.h>
#include <stdbool.h>
#include <apic.h>
#include <lapic.h>
#include <iopic.h>

void init_apic()
{
	/* Check Lapic */
	if (!lapic_check())
	{
		return;
		/* panic */
	}
	
	/* Get lapic physic addr */
	lapic.phys = lapic_get_base();
}