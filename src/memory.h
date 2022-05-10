//
// Created by shortping on 10.05.22.
//

#ifndef SLANG_MEMORY_H
#define SLANG_MEMORY_H


void SLANG_MEMORY_Init();
int SLANG_MEMORY_Add(void*);
void SLANG_MEMORY_Free();
void SLANG_MEMORY_ManFree(unsigned);
void* SLANG_MEMORY_GetValue(unsigned i);
#endif //SLANG_MEMORY_H
