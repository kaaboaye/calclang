//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#ifndef CALCLANG_ITEM_H
#define CALCLANG_ITEM_H

#include <stdio.h>
#include <stdbool.h>

#include "ItemType.h"
#include "ItemValue.h"

#define NUM_LEN 64

typedef struct {
  ItemType Type;
  ItemValue Value;
} Item;

bool ReadItem(Item *item, FILE *file);

#endif //CALCLANG_ITEM_H
