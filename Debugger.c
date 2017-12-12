//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include "Debugger.h"
#include "Item.h"
#include "ItemValue.h"

/**
 * Initializes debuggers static variables
 * @param err Error output file
 * @param warn Warning output file
 */
void DebuggerInit(FILE *err, FILE *warn) {
  wasSyntaxError = false;
  wasWarning = false;
  wasCompileError = false;
  wasRuntimeError = false;
  linesCount = 1;
  errorout = err;
  warnout = warn;
}

/**
 * stdio.h -> fgetc()s middleware.
 * Determines current line number.
 * @param f Input file
 * @return (int) Output char from fgetc() function
 */
int DebuggerGetC(FILE *f) {
  int c = fgetc(f);
  
  if (c == '\n') {
    linesCount++;
  }
  
  return c;
}

/**
 * stdio.h -> ungetc()s middleware.
 * Determines current line number.
 * @param c Char which will be given to ungetc()
 * @param f File which will be given to ungetc()
 * @return (int) Output char from ungetc() function
 */
int	DebuggerUnGetC(int c, FILE *f) {
  if (c == '\n') {
    linesCount--;
  }
  
  return ungetc(c, f);
}

/**
 * Returns current line number
 * @return Current line number
 */
unsigned int DebuggerGetLineNumber(void) {
  return linesCount;
}

/**
 * Determines whether there was any Syntax error
 * @return bool
 */
bool DebuggerGetWasSyntaxError(void) {
  return wasSyntaxError;
}

/**
 * Determines whether there was any Compile error
 * @return bool
 */
bool DebuggerGetWasCompileError(void) {
  return wasCompileError;
}

/**
 * Determines whether there was any Warning
 * @return bool
 */
bool DebuggerGetWasWarning(void) {
  return wasWarning;
}

/**
 * Prints an error to the error output.
 * Sets wasSyntaxError to true
 * @param line Line where error occured
 * @param err Error message
 */
void DebuggerSyntaxError(unsigned int line, const char *err) {
  wasSyntaxError = true;
  
  fprintf(errorout, "Line %d: Syntax error: %s\n", line, err);
}

/**
 * Prints an error to the error output
 * Sets wasSyntaxError to true
 * @param line Line where error occured
 * @param err Error message
 */
void DebuggerCompileError(unsigned int line, const char *err) {
  wasCompileError = true;
  
  fprintf(errorout, "Line %d: Compilation error: %s\n", line, err);
}

/**
 * Prints an error to the error output
 * Sets wasSyntaxError to true
 * @param line Line where error occured
 * @param err Error message
 */
void DebuggerRuntimeError(unsigned int line, const char *err) {
  wasRuntimeError = false;
  
  fprintf(errorout, "Line %d: Runtime error: %s\n", line, err);
}

/**
 * Prints an warning to the warning output
 * Sets wasSyntaxError to true
 * @param line Line where error occured
 * @param err Error message
 */
void DebuggerWarning(unsigned int line, const char *warn) {
  wasWarning = true;
  
  fprintf(warnout, "Line %d: Warning: %s\n", line, warn);
}

/**
 * Prints informations about given item
 * @param item Input item
 */
void DebuggerPrintItem(const Item *item) {
  fprintf(warnout, "Item: ");
  
  switch (item->Type){
    case type_number:
      gmp_fprintf(warnout, "Number: %Ff\n", item->Value.Number);
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