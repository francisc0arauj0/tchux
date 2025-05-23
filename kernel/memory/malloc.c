// Copyright 2022 by [Chris Palmer](https://noncombatant.org)
// SPDX-License-Identifier: Apache-2.0

#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <stdbool.h>

#include "malloc.h"

typedef struct Header {
  struct Header* next;
  size_t size;
  // Add padding if the `static_assert` below fires.
  // char _[count];
} Header;

// `long double` is (probably) the largest machine type. (If it’s not on your
// machine, change this `typedef`.) To ensure that allocations are properly
// aligned for all machine types, we assert that `Header` (the minimum unit of
// allocation) has the right size. This may require padding.
typedef long double Alignment;
static_assert(sizeof(Header) == sizeof(Alignment), "Add padding to `Header`");

static Header free_list;

// `NULL` is a sentinel value indicating that `free_list` has not yet been
// initialized.
static Header* free_list_start = NULL;

// We always request at least this amount from the operating system. The value
// should be chosen (a) to reduce pressure on the page table; and (b) to reduce
// the number of times we need to invoke the kernel.
static const size_t minimum_chunk_size = ((size_t)1 << 21) / sizeof(Header);

// Returns a pointer to a memory region containing at least `count`
// `Header`-sized objects.
//
// Returns `NULL` and sets `errno` if there was an error.
static Header* get_more_memory(size_t count) {
  if (count < minimum_chunk_size) {
    count = minimum_chunk_size;
  }
  Header* h = mmap(NULL, count * sizeof(Header), PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
  if (h == MAP_FAILED) {
    return NULL;
  }
  h->size = count;
  kr_free(h + 1);
  return free_list_start;
}

void* kr_malloc(size_t count, size_t size) {
  const size_t byte_count = count * size;
  if (byte_count < count || byte_count < size) {
    errno = EINVAL;
    return NULL;
  }

  // Round up to an integer number of `Header`-sized units, and add 1 to account
  // for the actual `Header` metadata that describes the region.
  const size_t unit_count =
      (byte_count + sizeof(Header) - 1) / sizeof(Header) + 1;

  Header* p;
  Header* previous;

  // Determine whether `free_list` has been initialized. Note that if it has not
  // been, the `for` loop below this one will fall through to the call to
  // `get_more_memory` on the 1st iteration.
  if ((previous = free_list_start) == NULL) {
    free_list.next = free_list_start = previous = &free_list;
    free_list.size = 0;
  }

  // Iterate down `free_list`, looking for regions large enough or requesting a
  // new region from the platform.
  for (p = previous->next; true; previous = p, p = p->next) {
    if (p->size >= unit_count) {
      if (p->size == unit_count) {
        // If this region is exactly the size we need, we're done.
        previous->next = p->next;
      } else {
        // If this region is larger than we need, return the tail end of it to
        // the caller, and adjust the size of the region `Header`.
        p->size -= unit_count;
        p += p->size;
        p->size = unit_count;
      }
      free_list_start = previous;
      return (void*)(p + 1);
    }

    // If we have wrapped around to the beginning of `free_list` (its end always
    // points to its beginning), we need to get more memory.
    if (p == free_list_start) {
      if ((p = get_more_memory(unit_count)) == NULL) {
        return NULL;
      }
    }
  }
}

void kr_free(void* p) {
  // The `Header` is always immediately before the region we returned to the
  // caller of `malloc`.
  Header* h = (Header*)p - 1;

  // Iterate over `free_list` looking for the segment containing `h`.
  Header* current;
  for (current = free_list_start; !(h > current && h < current->next);
       current = current->next) {
    if (current >= current->next && (h > current || h < current->next)) {
      // Freed block at start of end of arena.
      break;
    }
  }

  // If `h` is at the beginning of the segment, join it to the end.
  if (h + h->size == current->next) {
    h->size += current->next->size;
    h->next = current->next->next;
  } else {
    h->next = current->next;
  }

  // If `h` is at the end of the segment, join it to the beginning. These 2
  // joins ensure that we coalesce segments into larger segments.
  if (current + current->size == h) {
    current->size += h->size;
    current->next = h->next;
  } else {
    current->next = h;
  }

  free_list_start = current;
}