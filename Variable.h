//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_VARIABLE_H
#define CALCLANG_VARIABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Item.h"

#define MAX_VARIABLE_NAME_LEN 128

typedef struct {
  int Id; // Id of the variable
  char *Name; // Variable's name
  unsigned int Count; // Amount of items
  Item *Items; // Array of items
  Item *LastItem; // Last added item
} Variable;

Variable newVariable(void);
void VariableAddItem(Variable *v);
void VariableJoin(Variable *out, const Variable *in);
void VariableClean(Variable *v);
void VariableReadName(FILE *input, char *name, int len);

#endif //CALCLANG_VARIABLE_H
