//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_ITEMVALUE_H
#define CALCLANG_ITEMVALUE_H

#include <stdint.h>
#include <gmp.h>

#include "Operator.h"

typedef union {
  mpf_t Number;
  Operator Operator;
  void (*Procedure) (mpf_t);
  char *Name;
} ItemValue;


#endif //CALCLANG_ITEMVALUE_H
