//
// Created by shortping on 10.05.22.
//

#include "lifecycle.h"
#include "memory.h"
#include <stdlib.h>
#include "tokenizer/tokenizer.h"

// This method clears ALL memory used in this program | should be called instead of exit() or return in main function
void LifeCycle_Exit(unsigned code) {
    Memory_Free();
    Tokenizer_Invalidate();
    exit(code);
}