//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_ITEMSSTACK_H
#define CALCLANG_ITEMSSTACK_H

#include "Item.h"

typedef struct {
  unsigned int Count;
  Item *Items;
  Item *TopItem;
} ItemsStack;

ItemsStack newItemsStack(void);
void ItemsStackClean(ItemsStack *s);
void ItemsStackPush(ItemsStack *s, Item i);
bool ItemsStackPop(ItemsStack *s, Item *i);

#endif //CALCLANG_ITEMSSTACK_H
