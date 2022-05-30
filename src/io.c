//
// Created by shortping on 09.05.22.
//

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "lifecycle.h"
#include "tokenizer/tokenizer.h"

void IO_ReadFile(char* p) {
    FILE* fptr;
    fptr = fopen(p, "r");
    if(fptr == NULL) {
        printf("Error: Unable to read file \"%s\".\n", p);
        LifeCycle_Exit(1);
    }
    unsigned long filesize;
    fseek(fptr, 0L, SEEK_END);

    filesize = ftell(fptr) * sizeof(char); // Filesize

    char *text = malloc(filesize + 1);
    int txtId = Memory_Add(text);

    int buff;

    unsigned i = 0;
    fseek(fptr, 0L, 0L);
    while((buff = fgetc(fptr)) != EOF) {
        text[i++] = (char)buff;
    }
    text[filesize] = '\0';
    fclose(fptr);
    Tokenizer_Analyze(text);
    Memory_ManFree(txtId);
    // Make something with text lol

}