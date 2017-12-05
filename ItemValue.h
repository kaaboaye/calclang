//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_ITEMVALUE_H
#define CALCLANG_ITEMVALUE_H

#include <stdint.h>

#include "Operator.h"

typedef union {
  long double Number;
  Operator Operator;
  long double (*Procedure) (void);
  char *Name;
} ItemValue;


#endif //CALCLANG_ITEMVALUE_H
