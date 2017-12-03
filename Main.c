//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include <stdio.h>
#include "Lex.h"
#include "Storage.h"
#include "Debugger.h"

int main() {
  Storage storage = newStorage();
  FILE *input = stdin;
  FILE *output = stdout;
  FILE *errorout = stderr;
  
  DebuggerStart(errorout);

  LexStart(&storage, input);
  while (LexUpdate());
  
  return 0;
}
