#include "const.h"
#include "config.h"
#include "io.h"
#include "memory.h"
#include "lifecycle.h"
#include "tokenizer/tokenizer.h"
#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void config() {
    verboseMode = 0;
    memorySize = 128;
}

int main(int argc, char *argv[]) {
    config();

    for (int i = 0; i < argc; i++) {
        if (IS_OPT_VERBOSE(argv[i])) {
            verboseMode = 1;
        }
        if (IS_OPT_FILE(argv[i])) {
            fileName = argv[i + 1];
        }
        if (IS_OPT_VERBOSE(argv[i])) {
            memorySize = atol(argv[i + 1]);
        }
    }
    Memory_Init();
    if (fileName == NULL) {
        printf("Error: No file specified\n");
        LifeCycle_Exit(1);
    }
    if(verboseMode)
        printf("Loading File (%s)...\n", fileName);

    Tokenizer_Init();

    IO_ReadFile(fileName);

    LifeCycle_Exit(0);

    return 0;
}


