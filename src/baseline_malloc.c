#include "baseline_malloc.h"

#include <stdlib.h>

void *baseline_alloc(size_t size) {
    return malloc(size);
}

void baseline_free(void *ptr) {
    free(ptr);
}