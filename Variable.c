//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include <ctype.h>
#include "Variable.h"
#include "Debugger.h"

Variable newVariable(void) {
  Variable v;
  
  v.Count = 0;
  v.Items = (Item *) malloc(0);
  
  return v;
}

void VariableAddItem(Variable *v) {
  v->Count++;
  v->Items = (Item *) realloc(v->Items, (v->Count * sizeof(Item)));
  v->LastItem = &v->Items[v->Count - 1];
}

void VariableJoin(Variable *out, const Variable *in) {
  for (int i = 0; i < in->Count; ++i) {
    VariableAddItem(out);
    (*out->LastItem) = in->Items[i];
  }
}

void VariableClean(Variable *v) {
  free(v->Items);
  (*v) = newVariable();
}

void VariableReadName(FILE *input, char *name, int len) {
  int c;
  
  for (int i = 0; true; ++i) {
    c = DebuggerGetC(input);
    
    if (EOF == c) {
      name[i] = 0;
      return;
    }
    
    if (!isalnum(c)) {
      DebuggerUnGetC(c, input);
      name[i] = 0;
      return;
    }
    
    if (i == len - 1) {
      name[i] = 0;
      DebuggerSyntaxError(DebuggerGetLineNumber(), "Variable name is to long");
      return;
    }
    
    name[i] = (char)c;
  }
}
