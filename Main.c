//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include <stdio.h>
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

int main() {
  Storage storage = newStorage();
  FILE *input = fopen("input.txt", "r");
  FILE *output = stdout;
  FILE *errorout = stderr;
  FILE *warnout = stderr;
  
  DebuggerInit(errorout, warnout);
  
  // Read input
  LexInit(&storage, input);
  while (LexUpdate());
  
  if (DebuggerGetWasSyntaxError()) {
    return WAS_SYNTAX_ERROR;
  }
  
  // Compile to the ByteCode
  CompilerInit(&storage);
  CompilerCompile();
  
  if (DebuggerGetWasCompileError()) {
    return WAS_COMPILE_ERROR;
  }
  
  for (unsigned int x = 0; x < storage.ByteCodeCount; x++) {
    for (int i = 0; i < storage.ByteCode[x].Count; i++) {
      DebuggerPrintItem(&storage.ByteCode[x].Items[i]);
    }
  }
  
  return 0;
}
