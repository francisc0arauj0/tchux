#ifndef PMM_H
#define PMM_H

#include <stdint.h>

void init_pmm();
size_t pmm_allocate(int pages);

#endif