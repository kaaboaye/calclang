//
// Created by Mieszko Wawrzyniak on 05/12/2017.
//

#ifndef CALCLANG_COMPILER_H
#define CALCLANG_COMPILER_H

#include "Storage.h"

typedef struct {
  Storage *storage;
} Compiler;

Compiler newCompiler(Storage *s);

void CompilerCompile(Compiler *c);
void CompileVariables(Compiler *c, Variable *in, Variable *out);

#endif //CALCLANG_COMPILER_H
