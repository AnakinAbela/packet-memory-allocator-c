#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h>

void run_pool_benchmark(size_t block_size, size_t block_count, size_t operations);
void run_malloc_benchmark(size_t block_size, size_t operations);

#endif