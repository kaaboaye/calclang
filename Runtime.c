//
// Created by Mieszko Wawrzyniak on 05/12/2017.
//

#include "Runtime.h"
#include "Storage.h"
#include "Equation.h"
#include "Variable.h"
#include "Debugger.h"
#include "Item.h"
#include "ItemValue.h"

void RuntimeInit(Storage *s, FILE *out) {
  storage = s;
  output = out;
}

void RuntimeRun() {
  Variable *in;
  Item out;
  
  EquationInit();
  
  for (unsigned int i = 0; i < storage->ByteCodeCount; ++i) {
    in = &storage->ByteCode[i];
    
    // Solve an equation
    out = EquationRPNSolve(in);
    
    // Catch an error
    if (out.Type != type_number) {
      DebuggerRuntimeError(in[0].Items[0].Line, "Problem with calculating equation");
    }
    
    gmp_fprintf(output, "%Ff\n", out.Value.Number);
  }
}