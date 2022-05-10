//
// Created by shortping on 10.05.22.
//

#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

void **memoryPool;
int currentSize;
void* nullPtr;

void SLANG_MEMORY_Init() {
    memoryPool = malloc(sizeof(void *) * SLANG_CFG_MemorySize);
    currentSize = -1;
    nullPtr = malloc(1);

    if (SLANG_CFG_VerboseMode) {

        printf("Initialized NULLPTR at(%p)\n", nullPtr);
        printf("Initialized Memory-Manager (m_size:%lu, m_size_b:%lu, sp:%p, c_size:%d)\n", SLANG_CFG_MemorySize,
               SLANG_CFG_MemorySize * sizeof(void *), memoryPool, currentSize);
    }
    for(int i = 0; i < SLANG_CFG_MemorySize; i++) {
        memoryPool[i] = nullPtr;
    }
}

int SLANG_MEMORY_Add(void *ptr) {
    for (int i = 0; i < SLANG_CFG_MemorySize; i++) {
        if (memoryPool[i] == nullPtr) {
            if (SLANG_CFG_VerboseMode)
                printf("Added Value to MemoryManager at %d(%s) value: %p\n", i, (memoryPool[i] == nullPtr)?"NULL":"OV", ptr);

            memoryPool[i] = ptr;
            if (i > currentSize) {
                if (SLANG_CFG_VerboseMode)
                    printf("Incremented c_size to %d\n", i);
                currentSize = i;
            }
            return i;
            break;
        }
    }
    return -1;
}

void SLANG_MEMORY_ManFree(unsigned i) {
    if(i > SLANG_CFG_MemorySize) {
        printf("Error: Trying to free invalid memory\n");
        return;
    }
    if(memoryPool[i] == nullPtr) {
        printf("Error: Trying to free already freed memory\n");
        return;
    }
    if(SLANG_CFG_VerboseMode)
        printf("Manually freed PoolID (%d)\n", i);
    free(memoryPool[i]);
    memoryPool[i] = nullPtr;
}

void* SLANG_MEMORY_GetValue(unsigned i) {
    if(i > SLANG_CFG_MemorySize) {
        printf("Error: Trying to find invalid memory pointer");
        return nullPtr;
    }
    return memoryPool[i];
}

void SLANG_MEMORY_Free() {
    for (int i = 0; i < SLANG_CFG_MemorySize; i++) {
        if(memoryPool[i] != nullPtr)
            free(memoryPool[i]);
    }
    if (SLANG_CFG_VerboseMode)
        printf("Freed MemoryPool (%p)\n", memoryPool);
    free(memoryPool);
    free(nullPtr);
}