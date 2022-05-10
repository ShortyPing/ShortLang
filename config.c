//
// Created by shortping on 09.05.22.
//

#include "config.h"
#include "stdio.h"
unsigned SLANG_CFG_VerboseMode = 0;
char* SLANG_CFG_File;
void SLANG_CFG_SetVerbose(unsigned b) {
    SLANG_CFG_VerboseMode = b;
    printf("Verbose Mode: %s\n", b?"Enabled":"Disabled");
}
