//
// Created by Mieszko Wawrzyniak on 04/12/2017.
//

#include <string.h>
#include <math.h>
#include "NativeVariables.h"
#include "Equation.h"
#include "Variable.h"
#include "Item.h"
#include "ItemValue.h"

void NativeVariablesInit(void) {
  NativeVariablesCount = sizeof(variables) / sizeof(NativeVariable);
}

Variable NativeVariableGetByName(const char *name) {
  for (unsigned int i = 0; i < NativeVariablesCount; ++i) {
    if (strcmp(variables[i].Name, name) == 0) {
      return variables[i].Function();
    }
  }
  
  return newVariable();
}

Variable _ans() {
  Variable var = newVariable();
  
  VariableAddItem(&var);
  var.LastItem->Type = type_procedure;
  var.LastItem->Value.Procedure = EquationGetAns;
  
  return var;
}

Variable _pi() {
  Variable var = newVariable();
  
  VariableAddItem(&var);
  var.LastItem->Type = type_number;
  var.LastItem->Value.Number = M_PI;
  
  return var;
}

Variable _e() {
  Variable var = newVariable();
  
  VariableAddItem(&var);
  var.LastItem->Type = type_number;
  var.LastItem->Value.Number = M_E;
  
  return var;
}