//
// Created by pwpio on 6/1/2022.
//

#ifndef SLANG_TYPE_H
#define SLANG_TYPE_H

#include "../tokenizer/tokenizer.h"

typedef enum {
    TYPE_PRIMITIVE,
    TYPE_COMPLEX
} DataTypeType;

typedef enum {
    PRIMITIVE_INTEGER,
    PRIMITIVE_REAL,
    PRIMITIVE_STRING,       // Yes, I know a string is TECHNICALLY not a type on its own, but rather
                            // a pointer to the start of a character array ... Let's just ignore that
                            // here tho.
} PrimitiveType;

typedef struct DataType DataType;

typedef struct {
    Token *id;
    DataType *type;
} FieldPrototype;

typedef struct {
    unsigned len;
    FieldPrototype **fields;
} ComplexType;

struct DataType {
    DataTypeType type;
    union {
        struct { PrimitiveType type; } primitive;
        struct { Token *id; } complex;
    } detail;
};

#endif //SLANG_TYPE_H
