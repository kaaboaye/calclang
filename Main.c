//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include <stdio.h>
#include <float.h>
#include "Lex.h"
#include "Storage.h"
#include "Debugger.h"
#include "Variable.h"
#include "Equation.h"
#include "Item.h"
#include "ItemsStack.h"
#include "NativeVariables.h"
#include "ItemValue.h"
#include "Compiler.h"
#include "ExitCodes.h"
#include "Runtime.h"

int main(int argc, char *argv[]) {
  Storage storage = newStorage();
  FILE *input;
  
  if (argc == 2 && strcmp("-", argv[1]) == 0) {
    input = stdin;
  } else {
    input = fopen("input.txt", "r");
  }
  
  FILE *output = stdout;
  FILE *errorout = stderr;
  FILE *warnout = stderr;
  
  DebuggerInit(errorout, warnout);
  mpf_set_default_prec(512);
  
  { // Read input
    LexInit(&storage, input);
    while (LexUpdate());
  
  
    if (DebuggerGetWasSyntaxError()) {
      return WAS_SYNTAX_ERROR;
    }
  }
  
  { // Compile to the ByteCode
    Compiler compiler = newCompiler(&storage);
    CompilerCompile(&compiler);
  
    if (DebuggerGetWasCompileError()) {
      return WAS_COMPILE_ERROR;
    }
  }
  
  
  
  // Dump ByteCode
//  for (unsigned int x = 0; x < storage.ByteCodeCount; x++) {
//    for (int i = 0; i < storage.ByteCode[x].Count; i++) {
//      DebuggerPrintItem(&storage.ByteCode[x].Items[i]);
//    }
//  }
  
  // Run the ByteCode
  RuntimeInit(&storage, output);
  RuntimeRun();
  
  
  return 0;
}
