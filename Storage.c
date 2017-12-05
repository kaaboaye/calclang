//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include "Storage.h"
#include "Variable.h"

Storage newStorage(void) {
  Storage s;
  
  s.LexStorage = newVariable();
  
  s.ByteCodeCount = 0;
  s.ByteCode = (Variable *) malloc(0);
  
  s.VariablesCount = 0;
  s.Variables = (Variable *) malloc(0);
  
  return s;
}

void StorageAddVariable(Storage *s) {
  s->VariablesCount++;
  s->Variables = (Variable *) realloc(s->Variables, (s->VariablesCount * sizeof(Variable)));
  s->LastVariable = &s->Variables[s->VariablesCount - 1];
}

void StorageAddByteCode(Storage *s) {
  s->ByteCodeCount++;
  s->ByteCode = (Variable *) realloc(s->ByteCode, (s->ByteCodeCount * sizeof(Variable)));
  s->LastByteCode = &s->ByteCode[s->ByteCodeCount - 1];
}

Variable VariableFindByName(const Storage *s, const char *name) {
  for (unsigned int i = 0; i < s->VariablesCount; ++i) {
    if (strcmp(s->Variables[i].Name, name) == 0) {
      return s->Variables[i];
    }
  }
  
  return newVariable();
}
