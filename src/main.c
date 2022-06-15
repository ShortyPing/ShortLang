#include "const.h"
#include "config.h"
#include "io.h"
#include "memory.h"
#include "lifecycle.h"
#include "tokenizer/tokenizer.h"
#include "string.h"
#include "parser/ast.h"
#include "parser/parse.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void config() {
    verboseMode = 0;
    memorySize = 128;
}

int main(int argc, char *argv[]) {
    config();
    printf("ShortLang v%s made by (%s)\n", SLANG_VERSION, SLANG_AUTHORS);
    if (argc < 2) {
        printf("Error: No arguments.\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (IS_OPT_VERBOSE(argv[i])) {
            verboseMode = 1;
            continue;
        }
        if (IS_OPT_FILE(argv[i])) {
            fileName = argv[++ i];
            continue;
        }
        if (IS_OPT_HEAP(argv[i])) {
            memorySize = atol(argv[++ i]);
            continue;
        }
        printf("Error: Unknown command: %s\n", argv[i]);
        return 0;
    }
    Memory_Init();
    if (fileName == NULL) {
        printf("Error: No file specified\n");
        LifeCycle_Exit(1);
    }
    DEBUG("Loading File (%s)...\n", fileName);

    Tokenizer_Init();

    IO_ReadFile(fileName);

    Parser_Init();




    LifeCycle_Exit(0);

    return 0;
}


