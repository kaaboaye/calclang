//
// Created by Mieszko Wawrzyniak on 05/12/2017.
//


#ifndef CALCLANG_RUNTIME_H
#define CALCLANG_RUNTIME_H

#include "Storage.h"

static Storage *storage;
static FILE *output;

void RuntimeInit(Storage *s, FILE *out);
void RuntimeRun();


#endif //CALCLANG_RUNTIME_H
