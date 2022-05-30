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

void Memory_Init() {
    memoryPool = malloc(sizeof(void *) * memorySize);
    currentSize = -1;
    nullPtr = malloc(1);

    if (verboseMode) {

        printf("Initialized NULLPTR at(%p)\n", nullPtr);
        printf("Initialized Memory-Manager (m_size:%lu, m_size_b:%lu, sp:%p, c_size:%d)\n", memorySize,
               memorySize * sizeof(void *), memoryPool, currentSize);
    }
    for(int i = 0; i < memorySize; i++) {
        memoryPool[i] = nullPtr;
    }
}

int Memory_Add(void *ptr) {
    
    for (int i = 0; i < memorySize; i++) {
        if (memoryPool[i] == nullPtr) {
            if (verboseMode)
                printf("Added Value to MemoryManager at %d(%s) value: %p\n", i, (memoryPool[i] == nullPtr)?"NULL":"OV", ptr);

            memoryPool[i] = ptr;
            if (i > currentSize) {
                if (verboseMode)
                    printf("Incremented c_size to %d\n", i);
                currentSize = i;
            }
            return i;
            break;
        }
    }
    return -1;
}

void Memory_ManFree(unsigned i) {
    if(i > memorySize) {
        printf("Error: Trying to free invalid memory\n");
        return;
    }
    if(memoryPool[i] == nullPtr) {
        printf("Error: Trying to free already freed memory\n");
        return;
    }
    if(verboseMode)
        printf("Manually freed PoolID (%d)\n", i);
    free(memoryPool[i]);
    memoryPool[i] = nullPtr;
}

void* Memory_GetValue(unsigned i) {
    if(i > memorySize) {
        printf("Error: Trying to find invalid memory pointer");
        return nullPtr;
    }
    return memoryPool[i];
}

void Memory_Free() {
    for (int i = 0; i < memorySize; i++) {
        if(memoryPool[i] != nullPtr)
            free(memoryPool[i]);
    }
    if (verboseMode)
        printf("Freed MemoryPool (%p)\n", memoryPool);
    free(memoryPool);
    free(nullPtr);
}