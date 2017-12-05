//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include "Debugger.h"
#include "Item.h"
#include "ItemValue.h"

void DebuggerInit(FILE *err, FILE *warn) {
  wasSyntaxError = false;
  wasWarning = false;
  wasCompileError = false;
  wasRuntimeError = false;
  linesCount = 1;
  errorout = err;
  warnout = warn;
}

int DebuggerGetC(FILE *f) {
  int c = fgetc(f);
  
  if (c == '\n') {
    linesCount++;
  }
  
  return c;
}

int	DebuggerUnGetC(int c, FILE *f) {
  if (c == '\n') {
    linesCount--;
  }
  
  return ungetc(c, f);
}

unsigned int DebuggerGetLineNumber(void) {
  return linesCount;
}

bool DebuggerGetWasSyntaxError(void) {
  return wasSyntaxError;
}

bool DebuggerGetWasCompileError(void) {
  return wasCompileError;
}

bool DebuggerGetWasWarning(void) {
  return wasWarning;
}

void DebuggerSyntaxError(unsigned int line, const char *err) {
  wasSyntaxError = true;
  
  fprintf(errorout, "Line %d: Syntax error: %s\n", line, err);
}

void DebuggerCompileError(unsigned int line, const char *err) {
  wasCompileError = true;
  
  fprintf(errorout, "Line %d: Compilation error: %s\n", line, err);
}

void DebuggerRuntimeError(unsigned int line, const char *err) {
  wasRuntimeError = false;
  
  fprintf(errorout, "Line %d: Runtime error: %s\n", line, err);
}

void DebuggerWarning(unsigned int line, const char *warn) {
  wasWarning = true;
  
  fprintf(warnout, "Line %d: Warning: %s\n", line, warn);
}

void DebuggerPrintItem(const Item *item) {
  fprintf(warnout, "Item: ");
  
  switch (item->Type){
    case type_number:
      fprintf(warnout, "Number: %Lf\n", item->Value.Number);
      break;
    case type_operator:
      switch (item->Value.Operator) {
        case operator_addition:
          fputs("Operator: +\n", warnout);
          break;
        case operator_subtraction:
          fputs("Operator: -\n", warnout);
          break;
        case operator_multiplication:
          fputs("Operator: *\n", warnout);
          break;
        case operator_division:
          fputs("Operator: /\n", warnout);
          break;
        case operator_equals:
          fputs("Operator: =\n", warnout);
          break;
        case operator_left_bracket:
          fputs("Operator: (\n", warnout);
          break;
        case operator_right_bracket:
          fputs("Operator: )\n", warnout);
          break;
        case operator_semicolon:
          fputs("Operator: ;\n", warnout);
          break;
        case operator_colon:
          fprintf(warnout, "Operator: :\n");
          break;
      }
      break;
    case type_nan:
      fputs("Nan\n", warnout);
      break;
    case type_procedure:
      fprintf(warnout, "Procedure\n");
      break;
    case type_name:
      fprintf(warnout, "Name: %s\n", item->Value.Name);
      break;
  }
}