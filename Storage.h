//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_STORAGE_H
#define CALCLANG_STORAGE_H

#include <stdlib.h>
#include <string.h>

#include "Variable.h"

typedef struct {
  Variable LexStorage; // Variable with main code
  
  unsigned int ByteCodeCount; // Amount of Byte Code variables (equations, operations)
  Variable *ByteCode; // Variable with executable byte code
  Variable *LastByteCode;
  
  unsigned int VariablesCount; // Amount of items
  Variable *Variables; // Array of variables
  Variable *LastVariable; // Last used variable
  
} Storage;

Storage newStorage(void);

void StorageAddVariable(Storage *s);
void StorageAddByteCode(Storage *s);

Variable VariableFindByName(const Storage *s, const char *name);


#endif //CALCLANG_STORAGE_H
