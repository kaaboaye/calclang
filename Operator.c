//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include "Operator.h"
#include "MathHelpers.h"

int OperatorsCompare(const Operator o1, const Operator o2) {
  // Whether value is in range
  if (!(IN_RANGE(o1, operator_addition, operator_division) &&
      IN_RANGE(o2, operator_addition, operator_division)
  )) {
    return OUT_OF_RANGE;
  }
  
  return ((int)o1 - (int)o2);
}
