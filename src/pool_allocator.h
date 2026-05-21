#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stddef.h>

typedef struct PoolAllocator {
    size_t block_size;
    size_t block_count;
    size_t used_blocks;
    void *memory;
    void *free_list;
} PoolAllocator;

int pool_init(PoolAllocator *pool, size_t block_size, size_t block_count);
void *pool_alloc(PoolAllocator *pool);
void pool_free(PoolAllocator *pool, void *ptr);
void pool_destroy(PoolAllocator *pool);
void pool_print_stats(const PoolAllocator *pool);

#endif