//
// Created by shortping on 10.05.22.
//

#include "memory.h"
#include "config.h"
#include "const.h"
#include <stdlib.h>
#include <stdio.h>

void **memoryPool;
int currentSize;
void* nullPtr;

void Memory_Init() {
    memoryPool = malloc(sizeof(void *) * memorySize);
    currentSize = -1;
    nullPtr = malloc(1);

    DEBUG("Initialized NULLPTR at(%p)\n", nullPtr);
    DEBUG("Initialized Memory-Manager (m_size:%lu, m_size_b:%lu, sp:%p, c_size:%d)\n", memorySize,
           memorySize * sizeof(void *), memoryPool, currentSize);
    for(int i = 0; i < memorySize; i++) {
        memoryPool[i] = nullPtr;
    }
}

int Memory_Add(void *ptr) {
    
    for (int i = 0; i < memorySize; i++) {
        if (memoryPool[i] == nullPtr) {
            DEBUG("Added Value to MemoryManager at %d(%s) value: %p\n", i, (memoryPool[i] == nullPtr)?"NULL":"OV", ptr);

            memoryPool[i] = ptr;
            if (i > currentSize) {
                DEBUG("Incremented c_size to %d\n", i);
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
    DEBUG("Manually freed PoolID (%d)\n", i);
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
    DEBUG("Freed MemoryPool (%p)\n", memoryPool);
    free(memoryPool);
    free(nullPtr);
}