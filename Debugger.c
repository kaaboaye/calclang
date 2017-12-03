//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include "Debugger.h"

void DebuggerStart(FILE *out) {
  wasLexError = false;
  wasLexWarning = false;
  linesCount = 1;
  output = out;
}

void DebuggerWasNewLine(void) {
  linesCount++;
}

void DebuggerLexError(const char *err) {
  wasLexError = true;
  
  fprintf(output, "Line %d: Syntax error: %s\n", linesCount, err);
}

void DebuggerWarning(const char *warn) {
  wasLexWarning = true;
  
  fprintf(output, "Line %d: Warning: %s\n", linesCount, warn);
}