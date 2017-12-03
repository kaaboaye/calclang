//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_VARIABLE_H
#define CALCLANG_VARIABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Item.h"

typedef struct {
  int Count; // Ammount of items
  int NameId; // Id of variable's name
  Item *Items; // Array of items
  Item *LastItem; // Last added item
} Variable;

Variable newVariable(void);
void VariableAddItem(Variable *v);
bool ReadVariable(Variable *v, FILE *f);

#endif //CALCLANG_VARIABLE_H
