#include <stdio.h>
#include "const.h"
#include <string.h>
#include "config.h"
#include "f_read.h"

int main(int argc, char* argv[]) {
    printf("SLang Interpreter v%s made by %s\n", SLANG_VERSION, SLANG_AUTHORS);
    for(int i = 0; i < argc; i++) {
        if(!(strcmp(argv[i], "--verbose"))) {
            SLANG_CFG_SetVerbose(1);
        }
        if(!(strcmp(argv[i], "--file"))) {
            char* file = argv[i+1];
            if(file == NULL) {
                printf("Error: No file specified\n");
                return 1;
            }
            SLANG_CFG_File = file;
            printf("Loading File (%s)...\n", file);
            SLANG_FILE_ReadFile(file);
            return 0;
        }
    }
    printf("Error: Please define file with the --file flag.\n");
    return 0;
}
