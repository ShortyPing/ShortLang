//
// Created by shortping on 10.05.22.
//

#ifndef SLANG_MEMORY_H
#define SLANG_MEMORY_H

extern unsigned bufferSize;
extern unsigned posPtr;
extern void *nullPtr;

void Memory_Init(void);
int Memory_Add(void *);
void Memory_Free(void);
void Memory_ManFree(unsigned);
void* Memory_GetValue(unsigned);

#endif //SLANG_MEMORY_H
