#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <stdbool.h>
#include <stdatomic.h>

typedef atomic_flag spinlock;

void spinlock_acquire(spinlock *lock);
void spinlock_release(spinlock *lock);

#endif