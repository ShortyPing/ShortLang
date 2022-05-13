//
// Created by shortping on 10.05.22.
//

#ifndef SLANG_MEMORY_H
#define SLANG_MEMORY_H

extern unsigned bufferSize;
extern unsigned posPtr;
extern void* nullPtr;

void SLANG_MEMORY_Init(void);
int SLANG_MEMORY_Add(void*);
void SLANG_MEMORY_Free(void);
void SLANG_MEMORY_ManFree(unsigned);
void* SLANG_MEMORY_GetValue(unsigned i);
#endif //SLANG_MEMORY_H
