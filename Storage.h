//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_STORAGE_H
#define CALCLANG_STORAGE_H

#include <stdlib.h>
#include <string.h>

#include "Variable.h"
#include "VariableName.h"

typedef struct {
  unsigned int VariablesCount; // Ammount of items
  Variable *Variables; // Array of variables
  Variable *LastVariable; // Last used variable
  
  int VariableNamesCount; // Ammount of variable names
  VariableName *Names; // List of variable names
  VariableName *LastName; // Last used variable name
} Storage;

Storage newStorage(void);
void StorageAddVariable(Storage *s);
void StorageAddVariableName(Storage *s, const unsigned char *name);
void StorageAssignNameVariable(Storage *s, const unsigned char *name, Variable *var);

#endif //CALCLANG_STORAGE_H
