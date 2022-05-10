#include <stdio.h>
#include "const.h"
#include <string.h>
#include "config.h"
#include "f_read.h"
#include "memory.h"
#include "lifecycle.h"
#include <stdlib.h>
void SLANG_Conf() {
    SLANG_CFG_VerboseMode = 0;
    SLANG_CFG_MemorySize = 128;
}

int main(int argc, char* argv[]) {
    printf("SLang Interpreter v%s made by %s\n", SLANG_VERSION, SLANG_AUTHORS);

    SLANG_Conf();

    for(int i = 0; i < argc; i++) {
        if(!(strcmp(argv[i], "--verbose"))) {
            SLANG_CFG_VerboseMode = 1;
        }
        if(!(strcmp(argv[i], "--file"))) {
            SLANG_CFG_File = argv[i+1];

        }
    }
    SLANG_MEMORY_Init();
    if(SLANG_CFG_File == NULL) {
        printf("Error: No file specified\n");
        SLANG_LIFECYCLE_Exit(1);
    }
    printf("Loading File (%s)...\n", SLANG_CFG_File);


    SLANG_FILE_ReadFile(SLANG_CFG_File);
    SLANG_LIFECYCLE_Exit(0);
    return 0;
}


