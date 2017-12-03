//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include "Variable.h"

Variable newVariable(void) {
  Variable v;
  
  v.Count = 0;
  v.Items = (Item *) malloc(0);
  
  return v;
}

void VariableAddItem(Variable *v) {
  v->Count++;
  v->Items = (Variable *) realloc(v->Items, v->Count);
  v->LastItem = &v->Items[v->Count - 1];
}

bool ReadVariable(Variable *var, FILE *f) {
  
  return true;
}