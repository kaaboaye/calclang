//
// Created by Mieszko Wawrzyniak on 05/12/2017.
//

#ifndef CALCLANG_COMPILER_H
#define CALCLANG_COMPILER_H

#include "Storage.h"

static Storage *storage;

void CompilerInit(Storage *s);
void CompilerCompile();

#endif //CALCLANG_COMPILER_H
