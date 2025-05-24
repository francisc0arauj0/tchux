#include <spinlock.h>
#include <stdatomic.h>

void spinlock_acquire(spinlock *lock)
{
	while(atomic_flag_test_and_set_explicit(lock, memory_order_acquire))
	{
		/* busy-wait */
	}
}

void spinlock_release(spinlock *lock)
{
	atomic_flag_clear_explicit(lock, memory_order_release);
}