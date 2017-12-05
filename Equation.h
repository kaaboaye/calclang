//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_EQUATION_H
#define CALCLANG_EQUATION_H

#include "Item.h"
#include "Variable.h"
#include "ItemsStack.h"

static long double equationAns;

void EquationInit();
Item EquationSolve(const Variable *in);
Item EquationRPNSolve(const Variable *in);
void EquationToRPN(const Variable *in, Variable *out);
long double EquationGetAns();

#endif //CALCLANG_EQUATION_H
