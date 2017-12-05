//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_DEBUGGER_H
#define CALCLANG_DEBUGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Item.h"

#define LINE_LEN 256

static FILE *errorout;
static FILE *warnout;
static unsigned int linesCount;
static bool wasSyntaxError;
static bool wasCompileError;
static bool wasWarning;
static bool wasRuntimeError;

unsigned int DebuggerGetLineNumber(void);
bool DebuggerGetWasSyntaxError(void);
bool DebuggerGetWasCompileError(void);
bool DebuggerGetWasWarning(void);

void DebuggerInit(FILE *err, FILE *warn);
int DebuggerGetC(FILE *f);
int	DebuggerUnGetC(int c, FILE *f);
void DebuggerSyntaxError(unsigned int line, const char *err);
void DebuggerCompileError(unsigned int line, const char *err);
void DebuggerRuntimeError(unsigned int line, const char *err);
void DebuggerWarning(unsigned int line, const char *warn);
void DebuggerPrintItem(const Item *item);

#endif //CALCLANG_DEBUGGER_H
