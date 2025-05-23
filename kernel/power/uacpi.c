#include <stdint.h>
#include <uacpi/uacpi.h>
#include <malloc.h>
#include <ports.h>

void init_acpi()
{
}

/* malloc */
void *uacpi_kernel_alloc(uacpi_size size)
{
	return kr_malloc(1, size);
}

void uacpi_kernel_free(void *mem)
{
	kr_free(mem);
}

/* IO */
uacpi_status uacpi_kernel_io_map(uacpi_io_addr base, uacpi_size len, uacpi_handle *out_handle)
{
	(void)len;
	*out_handle = (void *)base;
	return UACPI_STATUS_OK;
}

void uacpi_kernel_io_unmap(uacpi_handle handle)
{
	(void)handle;
}


/* IO Read */
uacpi_status uacpi_kernel_io_read(uacpi_handle handle, uacpi_size offset, uacpi_u8 width, uacpi_u64 *out_value)
{
	uacpi_io_addr target = (uacpi_io_addr)handle + offset;
	switch (width)
	{
		case 1:
			*out_value = inportb(target);
			break;
		case 2:
			*out_value = inportw(target);
			break;
		case 4:
			*out_value = inportl(target);
			break;
		default:
			return UACPI_STATUS_INVALID_ARGUMENT;
	}
	return UACPI_STATUS_OK;
}

uacpi_status uacpi_kernel_io_read8(uacpi_handle handle, uacpi_size offset, uacpi_u8 *out_value)
{
	return uacpi_kernel_io_read(handle, offset, 1, (uacpi_u64 *)out_value);
}

uacpi_status uacpi_kernel_io_read16(uacpi_handle handle, uacpi_size offset, uacpi_u16 *out_value)
{
	return uacpi_kernel_io_read(handle, offset, 2, (uacpi_u64 *)out_value);
}

uacpi_status uacpi_kernel_io_read32(uacpi_handle handle, uacpi_size offset, uacpi_u32 *out_value)
{
	return uacpi_kernel_io_read(handle, offset, 4, (uacpi_u64 *)out_value);
}

/* IO Write */
uacpi_status uacpi_kernel_io_write(uacpi_handle handle, uacpi_size offset, uacpi_u8 width, uacpi_u64 value)
{
	uacpi_io_addr target = (uacpi_io_addr)handle + offset;
	switch (width)
	{
		case 1:
			outportb(target, value);
			break;
		case 2:
			outportw(target, value);
			break;
		case 4:
			outportl(target, value);
			break;
		default:
			return UACPI_STATUS_INVALID_ARGUMENT;
	}
	return UACPI_STATUS_OK;
}

uacpi_status uacpi_kernel_io_write8(uacpi_handle handle, uacpi_size offset, uacpi_u8 in_value)
{
	return uacpi_kernel_io_write(handle, offset, 1, in_value);
}

uacpi_status uacpi_kernel_io_write16(uacpi_handle handle, uacpi_size offset, uacpi_u16 in_value)
{
	return uacpi_kernel_io_write(handle, offset, 2, in_value);
}

uacpi_status uacpi_kernel_io_write32(uacpi_handle handle, uacpi_size offset, uacpi_u32 in_value)
{
	return uacpi_kernel_io_write(handle, offset, 4, in_value);
}