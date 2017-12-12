//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_EQUATION_H
#define CALCLANG_EQUATION_H

#include "Item.h"
#include "Variable.h"
#include "ItemsStack.h"

static mpf_t equationAns;

void EquationInit();
Item EquationSolve(const Variable *in);
Item EquationRPNSolve(const Variable *in);
void EquationToRPN(const Variable *in, Variable *out);
void EquationGetAns(mpf_t num);

#endif //CALCLANG_EQUATION_H
