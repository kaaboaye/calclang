//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_ITEM_H
#define CALCLANG_ITEM_H

#include <stdio.h>
#include <stdbool.h>

#include "ItemType.h"
#include "ItemValue.h"

#define NUM_LEN 512

#define END_OF_EXPRESSION(item) ( \
  item->Type == type_operator && ( \
    item->Value.Operator == operator_equals || \
    item->Value.Operator == operator_semicolon ))

typedef struct {
  ItemType Type;
  ItemValue Value;
  unsigned int Line;
} Item;

bool ReadItem(Item *item, FILE *file);
Item ItemCalc(const Item b, const Item operator, const Item a);

#endif //CALCLANG_ITEM_H
