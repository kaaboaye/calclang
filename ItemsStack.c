//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include <stdlib.h>
#include "ItemsStack.h"

ItemsStack newItemsStack(void) {
  ItemsStack s;
  
  s.Count = 0;
  s.Items = (Item *) malloc(0);
  
  return s;
}

void ItemsStackClean(ItemsStack *s) {
  free(s->Items);
  (*s) = newItemsStack();
}

void ItemsStackPush(ItemsStack *s, Item i) {
  // Extend array
  s->Count++;
  s->Items = (Item *) realloc(s->Items, (s->Count * sizeof(Item)));
  
  // Set top item
  s->TopItem = &s->Items[s->Count -1];
  
  // Save item
  (*s->TopItem) = i;
}

bool ItemsStackPop(ItemsStack *s, Item *i) {
  // Check whether the stack is empty
  if (s->Count == 0) {
    return false;
  }
  
  // Set output item
  (*i) = (*s->TopItem);
  
  // Free up space
  s->Count--;
  s->Items = (Item *) realloc(s->Items, (s->Count * sizeof(Item)));
  
  // Set top item
  s->TopItem = &s->Items[s->Count -1];
  
  return true;
}