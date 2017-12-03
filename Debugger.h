//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_DEBUGGER_H
#define CALCLANG_DEBUGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_LEN 256

static FILE *output;
static unsigned int linesCount;
static bool wasLexError;
static bool wasLexWarning;

void DebuggerStart(FILE *out);
void DebuggerWasNewLine(void);
void DebuggerLexError(const char *err);
void DebuggerWarning(const char *warn);

#endif //CALCLANG_DEBUGGER_H
