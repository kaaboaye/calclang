//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include <ctype.h>
#include "Item.h"
#include "ItemValue.h"
#include "Debugger.h"

bool ReadItem(Item *item, FILE *file) {
  int c;
  
  if (EOF == (c = fgetc(file))) {
    return false;
  }
  
  // Detect addiction
  if (c == '+') {
    item->Type = type_operator;
    item->Value.Operator = operator_addition;

    return true;
  }
  
  // Detect subtraction
  if (c == '-') {
    item->Type = type_operator;
    item->Value.Operator = operator_subtraction;
    
    return true;
  }
  
  // Detect equals
  if (c == '=') {
    item->Type = type_operator;
    item->Value.Operator = operator_equals;
    
    return true;
  }
  
  // Detect number
  if (isdigit(c)) {
    unsigned char snum[NUM_LEN];
    unsigned int i = 1;
    bool isInt = true;
    
    // Read the number
    snum[0] = c;
    while (EOF != (c = fgetc(file))) {
      // Detect second dot in the number. What's not good.
      if (!isInt && c == '.') {
        DebuggerLexError("Illegal second dot in number");
        return false;
      }
      // Detect first dot in the number
      else if (isInt && c == '.') {
        isInt = false;
      }
      // Detect end of the number.
      else if (!(isdigit(c) || c == '.')) {
        ungetc(c, file);
        snum[i] = 0;
        break;
      }
      
      // Prevent overflow
      if (i >= NUM_LEN - 1) {
        DebuggerLexError("Number overflow");
        return false;
      }
      
      snum[i] = c;
      i++;
    }
    
    if (isInt) {
      item->Type = type_int;
      item->Value.Int = (int64_t) strtol(snum, NULL, 10);
      return true;
    }
    
    item->Type = type_float;
    item->Value.Float = strtold(snum, NULL);
    return true;
  }
  
  // Not found
  {
    unsigned char err[LINE_LEN];
    sprintf(err, "Unknown item %c", c);
    DebuggerLexError(err);
    return false;
  }
}