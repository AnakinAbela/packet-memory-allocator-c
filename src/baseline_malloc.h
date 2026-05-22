#ifndef BASELINE_MALLOC_H
#define BASELINE_MALLOC_H

#include <stddef.h>

void *baseline_alloc(size_t size);
void baseline_free(void *ptr);

#endif