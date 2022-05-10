//
// Created by shortping on 10.05.22.
//

#include "lifecycle.h"
#include "memory.h"
#include <stdlib.h>
#include "code/tokenizer.h"

void SLANG_LIFECYCLE_Exit(unsigned code) {
    SLANG_MEMORY_Free();
    SLANG_Tokenizer_Invalidate();
    exit(code);
}