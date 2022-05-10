//
// Created by shortping on 09.05.22.
//

#include "f_read.h"
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "lifecycle.h"

void SLANG_FILE_ReadFile(char* p) {
    FILE* fptr;
    fptr = fopen(p, "r");
    if(fptr == NULL) {
        printf("Error: Specified file not found or not enough permissions\n");
        SLANG_LIFECYCLE_Exit(1);
    }
    unsigned long filesize;
    fseek(fptr, 0L, SEEK_END);

    filesize = ftell(fptr) * sizeof(char); // Filesize

    char *text = malloc(filesize + 1);
    SLANG_MEMORY_Add(text);
    int buff;

    unsigned i = 0;
    fseek(fptr, 0L, 0L);
    while((buff = fgetc(fptr)) != EOF) {
        text[i++] = (char)buff;
    }
    text[filesize] = '\0';
    fclose(fptr);

    // Make something with text lol
}