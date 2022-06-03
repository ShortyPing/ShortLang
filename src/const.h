//
// Created by shortping on 09.05.22.
//

#ifndef SLANG_VERSION
#   define SLANG_VERSION "0.0.1"
#endif

#ifndef SLANG_AUTHORS
#   define SLANG_AUTHORS "Michael Steinmoetzger, Piotr Krzysztof Wyrwas"
#endif

#ifndef OPT_VERBOSE
#   define OPT_VERBOSE "--verbose"
#endif

#ifndef OPT_VERBOSE_SHORT
#   define OPT_VERBOSE_SHORT "-v"
#endif

#ifndef OPT_FILE
#   define OPT_FILE "--file"
#endif

#ifndef OPT_FILE_SHORT
#   define OPT_FILE_SHORT "-f"
#endif

#ifndef OPT_HEAP
#   define OPT_HEAP "--heap"
#endif

#ifndef OPT_HEAP_SHORT
#   define OPT_HEAP_SHORT "-h"
#endif

#ifndef IS_OPT_VERBOSE
#   define IS_OPT_VERBOSE(x) \
            (!strcmp(x, OPT_VERBOSE) || !strcmp(x, OPT_VERBOSE_SHORT))
#endif

#ifndef IS_OPT_FILE
#   define IS_OPT_FILE(x) \
            (!strcmp(x, OPT_FILE) || !strcmp(x, OPT_FILE_SHORT))
#endif

#ifndef IS_OPT_HEAP
#   define IS_OPT_HEAP(x) \
            (!strcmp(x, OPT_HEAP) || !strcmp(x, OPT_HEAP_SHORT))
#endif

#ifndef DEBUG
#   define DEBUG(...) \
            if (verboseMode) {          \
                printf("[Debug: %s] ", __func__);   \
                printf(__VA_ARGS__); \
            }
#endif
