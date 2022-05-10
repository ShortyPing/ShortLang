//
// Created by shortping on 09.05.22.
//

#include "f_read.h"
#include <stdio.h>
#include <stdlib.h>
void SLANG_FILE_ReadFile(char* p) {
    FILE *fptr = fopen(p, "r");
    if(fptr == NULL) {
        printf("Error: Specified file not found or not enough permissions\n");
        exit(1);
    }
    unsigned long filesize;
    fseek(fptr, 0L, SEEK_END);
    filesize = ftell(fptr) * sizeof(char); // Filesize
    char text[filesize + 1];
    char buff;
    fscanf(fptr, "%c", &buff);
    unsigned i;
    fseek(fptr, 0L, 0L);
    while((buff = fgetc(fptr)) != EOF) {
        text[i++] = (char)buff;
    }
    text[filesize] = '\0';

    // Make something with text lol
}