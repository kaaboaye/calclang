//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_OPERATOR_H
#define CALCLANG_OPERATOR_H

#define OUT_OF_RANGE -1001

typedef enum {
  operator_addition,
  operator_subtraction,
  operator_multiplication,
  operator_division,
  operator_left_bracket,
  operator_right_bracket,
  operator_equals,
  operator_colon,
  operator_semicolon,
} Operator;

int OperatorsCompare(const Operator o1, const Operator o2);

#endif //CALCLANG_OPERATOR_H
