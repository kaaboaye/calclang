//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include "Storage.h"
#include "VariableName.h"
#include "Variable.h"

Storage newStorage(void) {
  Storage s;
  
  s.VariablesCount = 0;
  s.Variables = (Variable *) malloc(0);
  
  s.VariableNamesCount = 0;
  s.Names = (VariableName *) malloc(0);
  
  return s;
}

void StorageAddVariable(Storage *s) {
  s->VariablesCount++;
  s->Variables = (Variable *) realloc(s->Variables, (s->VariablesCount * sizeof(Variable)));
  s->LastVariable = &s->Variables[s->VariablesCount - 1];
  
  s->LastVariable->NameId = VAR_UNNAMED;
}

void StorageAddVariableName(Storage *s, const unsigned char *name) {
  s->VariableNamesCount++;
  s->Names = (VariableName *) realloc(s->Variables, (s->VariableNamesCount * sizeof(VariableName)));
  
  s->LastName = &s->Names[s->VariableNamesCount -1];
  s->LastName->Name = malloc(strlen(name) + 1);
  strcpy(s->LastName->Name, name);
}

void StorageAssignNameVariable(Storage *s, const unsigned char *name, Variable *var) {
  StorageAddVariableName(s, name);
  
  var->NameId = s->VariableNamesCount - 1;
}