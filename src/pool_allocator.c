#include "pool_allocator.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct FreeNode {
    struct FreeNode *next;
} FreeNode;

int pool_init(PoolAllocator *pool, size_t block_size, size_t block_count) {
    if (pool == NULL || block_size == 0 || block_count == 0) {
        return 0;
    }

    if (block_size < sizeof(FreeNode)) {
        block_size = sizeof(FreeNode);
    }

    pool->block_size = block_size;
    pool->block_count = block_count;
    pool->used_blocks = 0;
    pool->memory = malloc(block_size * block_count);
    pool->free_list = NULL;

    if (pool->memory == NULL) {
        return 0;
    }

    uint8_t *base = (uint8_t *)pool->memory;

    for (size_t i = 0; i < block_count; i++) {
        FreeNode *node = (FreeNode *)(base + i * block_size);
        node->next = (FreeNode *)pool->free_list;
        pool->free_list = node;
    }

    return 1;
}

void *pool_alloc(PoolAllocator *pool) {
    if (pool == NULL || pool->free_list == NULL) {
        return NULL;
    }

    FreeNode *node = (FreeNode *)pool->free_list;
    pool->free_list = node->next;
    pool->used_blocks++;

    return (void *)node;
}

void pool_free(PoolAllocator *pool, void *ptr) {
    if (pool == NULL || ptr == NULL) {
        return;
    }

    FreeNode *node = (FreeNode *)ptr;
    node->next = (FreeNode *)pool->free_list;
    pool->free_list = node;

    if (pool->used_blocks > 0) {
        pool->used_blocks--;
    }
}

void pool_destroy(PoolAllocator *pool) {
    if (pool == NULL) {
        return;
    }

    free(pool->memory);
    pool->memory = NULL;
    pool->free_list = NULL;
    pool->block_size = 0;
    pool->block_count = 0;
    pool->used_blocks = 0;
}

void pool_print_stats(const PoolAllocator *pool) {
    if (pool == NULL) {
        return;
    }

    size_t free_blocks = pool->block_count - pool->used_blocks;

    printf("Pool stats:\n");
    printf("  block size  : %zu bytes\n", pool->block_size);
    printf("  block count : %zu\n", pool->block_count);
    printf("  used blocks : %zu\n", pool->used_blocks);
    printf("  free blocks : %zu\n", free_blocks);
}