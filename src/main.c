#include <stdio.h>

#include "pool_allocator.h"
#include "benchmark.h"

int main(void) {
    PoolAllocator pool;

    if (!pool_init(&pool, 64, 8)) {
        fprintf(stderr, "Failed to initialize pool allocator.\n");
        return 1;
    }

    printf("Initial allocator validation:\n");
    pool_print_stats(&pool);
    printf("\n");

    void *a = pool_alloc(&pool);
    void *b = pool_alloc(&pool);
    void *c = pool_alloc(&pool);

    printf("After allocating 3 blocks:\n");
    pool_print_stats(&pool);
    printf("\n");

    printf("Allocated pointers:\n");
    printf("  a = %p\n", a);
    printf("  b = %p\n", b);
    printf("  c = %p\n", c);
    printf("\n");

    pool_free(&pool, b);

    printf("After freeing block b:\n");
    pool_print_stats(&pool);
    printf("\n");

    void *d = pool_alloc(&pool);

    printf("After allocating one more block:\n");
    pool_print_stats(&pool);
    printf("  d = %p\n", d);
    printf("\n");

    pool_destroy(&pool);

    printf("Benchmark comparison:\n\n");
    run_pool_benchmark(64, 10000, 10000);
    run_malloc_benchmark(64, 10000);

    return 0;
}