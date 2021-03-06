//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_LEX_H
#define CALCLANG_LEX_H

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#include "Debugger.h"
#include "Storage.h"

static Storage *storage;
static Variable tmpVar;
static FILE *input;
static bool isReadingComment;

void LexInit(Storage *s, FILE *in);
bool LexUpdate(void);

#endif //CALCLANG_LEX_H
