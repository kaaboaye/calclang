//
// Created by Mieszko Wawrzyniak on 04/12/2017.
//

#ifndef CALCLANG_NATIVEVARIABLES_H
#define CALCLANG_NATIVEVARIABLES_H

#include "Item.h"
#include "Variable.h"

typedef struct {
  char *Name;
  Variable (*Function) (void);
} NativeVariable;

static int NativeVariablesCount;

void NativeVariablesInit(void);
Variable NativeVariableGetByName(const char *name);

Variable _ans(void);
Variable _pi(void);
Variable _e(void);

static NativeVariable variables[] = {
    // Variable name, Is constant, Pointer to the function
    {"ans", _ans},
    {"pi", _pi},
    {"e", _e},
};

#endif //CALCLANG_NATIVEVARIABLES_H
