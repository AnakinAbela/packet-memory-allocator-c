#include "benchmark.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pool_allocator.h"
#include "baseline_malloc.h"

static double get_elapsed_seconds(clock_t start, clock_t end) {
    return (double)(end - start) / (double)CLOCKS_PER_SEC;
}

void run_pool_benchmark(size_t block_size, size_t block_count, size_t operations) {
    PoolAllocator pool;
    void **ptrs = NULL;
    clock_t start;
    clock_t end;

    if (!pool_init(&pool, block_size, block_count)) {
        fprintf(stderr, "Failed to initialize pool allocator for benchmark.\n");
        return;
    }

    ptrs = malloc(sizeof(void *) * operations);
    if (ptrs == NULL) {
        fprintf(stderr, "Failed to allocate pointer array for pool benchmark.\n");
        pool_destroy(&pool);
        return;
    }

    start = clock();

    size_t allocated = 0;
    for (size_t i = 0; i < operations; i++) {
        ptrs[i] = pool_alloc(&pool);
        if (ptrs[i] == NULL) {
            break;
        }
        allocated++;
    }

    for (size_t i = 0; i < allocated; i++) {
        pool_free(&pool, ptrs[i]);
    }

    end = clock();

    printf("Pool benchmark:\n");
    printf("  block size   : %zu bytes\n", block_size);
    printf("  block count  : %zu\n", block_count);
    printf("  operations   : %zu requested, %zu completed\n", operations, allocated);
    printf("  elapsed time : %.6f seconds\n", get_elapsed_seconds(start, end));
    printf("\n");

    free(ptrs);
    pool_destroy(&pool);
}

void run_malloc_benchmark(size_t block_size, size_t operations) {
    void **ptrs = NULL;
    clock_t start;
    clock_t end;

    ptrs = malloc(sizeof(void *) * operations);
    if (ptrs == NULL) {
        fprintf(stderr, "Failed to allocate pointer array for malloc benchmark.\n");
        return;
    }

    start = clock();

    size_t allocated = 0;
    for (size_t i = 0; i < operations; i++) {
        ptrs[i] = baseline_alloc(block_size);
        if (ptrs[i] == NULL) {
            break;
        }
        allocated++;
    }

    for (size_t i = 0; i < allocated; i++) {
        baseline_free(ptrs[i]);
    }

    end = clock();

    printf("Malloc benchmark:\n");
    printf("  block size   : %zu bytes\n", block_size);
    printf("  operations   : %zu requested, %zu completed\n", operations, allocated);
    printf("  elapsed time : %.6f seconds\n", get_elapsed_seconds(start, end));
    printf("\n");

    free(ptrs);
}