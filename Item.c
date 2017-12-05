//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include <ctype.h>
#include <memory.h>
#include "Item.h"
#include "ItemValue.h"
#include "Debugger.h"
#include "Variable.h"

bool ReadItem(Item *item, FILE *file) {
  int c;
  
  item->Line = DebuggerGetLineNumber();
  
  // Try to read character
  if (EOF == (c = DebuggerGetC(file))) {
    return false;
  }
  
  // Set default type
  item->Type = type_nan;
  
  // Detect + addiction
  if (c == '+') {
    item->Type = type_operator;
    item->Value.Operator = operator_addition;

    return true;
  }
  
  // Detect - subtraction
  if (c == '-') {
    item->Type = type_operator;
    item->Value.Operator = operator_subtraction;
    
    return true;
  }
  
  // Detect * multiplication
  if (c == '*') {
    item->Type = type_operator;
    item->Value.Operator = operator_multiplication;
    
    return true;
  }
  
  // Detect / division
  if (c == '/') {
    item->Type = type_operator;
    item->Value.Operator = operator_division;
    
    return true;
  }
  
  // Detect = equals
  if (c == '=') {
    item->Type = type_operator;
    item->Value.Operator = operator_equals;
    
    return true;
  }
  
  // Detect ( left bracket
  if (c == '(') {
    item->Type = type_operator;
    item->Value.Operator = operator_left_bracket;
    
    return true;
  }
  
  // Detect ) right bracket
  if (c == ')') {
    item->Type = type_operator;
    item->Value.Operator = operator_right_bracket;
    
    return true;
  }
  
  // Detect : colon
  if (c == ':') {
    item->Type = type_operator;
    item->Value.Operator = operator_colon;
    
    return true;
  }
  
  // Detect ; semicolon
  if (c == ';') {
    item->Type = type_operator;
    item->Value.Operator = operator_semicolon;
    
    return true;
  }
  
  // Detect number
  if (isdigit(c)) {
    char snum[NUM_LEN];
    unsigned int i = 1;
    bool isInt = true;
    
    // Read the number
    snum[0] = c;
    while (EOF != (c = DebuggerGetC(file))) {
      // Detect second dot in the number. What's not good.
      if (!isInt && c == '.') {
        DebuggerSyntaxError(item->Line, "Illegal second dot in number");
        return false;
      }
      // Detect first dot in the number
      else if (isInt && c == '.') {
        isInt = false;
      }
      // Detect end of the number.
      else if (!(isdigit(c) || c == '.')) {
        DebuggerUnGetC(c, file);
        snum[i] = 0;
        break;
      }
      
      // Prevent overflow
      if (i >= NUM_LEN - 1) {
        DebuggerSyntaxError(item->Line, "Number overflow");
        
        // Read from input the rest of number.
        while (EOF != (c = DebuggerGetC(file))) {
          if (!(isdigit(c) || c == '.')) {
            DebuggerUnGetC(c, file);
            item->Type = type_number;
            break;
          }
        }
        
        return false;
      }
      
      snum[i] = c;
      i++;
    }
    
    item->Type = type_number;
    item->Value.Number = strtold(snum, NULL);
    return true;
  }
  
  // Detect name
  if (isalpha(c)) {
    DebuggerUnGetC(c, file);
  
    Variable var;
    char name[MAX_VARIABLE_NAME_LEN];
  
    VariableReadName(file, name, MAX_VARIABLE_NAME_LEN);
    
    item->Type = type_name;
    item->Value.Name = (char *) malloc(MAX_VARIABLE_NAME_LEN);
    strcpy(item->Value.Name, name);
  
    return true;
  }
  
  // Not found
  {
    char err[LINE_LEN];
    sprintf(err, "Unknown item %c", c);
    DebuggerSyntaxError(item->Line, err);
    return false;
  }
}

Item ItemCalc(const Item b, const Item operator, const Item a) {
  Item result;
  
  // Set result type
  result.Type = type_number;
  
  // Calc the result as float
  switch (operator.Value.Operator) {
    case operator_addition:
      result.Value.Number = a.Value.Number + b.Value.Number;
      break;
    case operator_subtraction:
      result.Value.Number = a.Value.Number - b.Value.Number;
      break;
    case operator_multiplication:
      result.Value.Number = a.Value.Number * b.Value.Number;
      break;
    case operator_division:
      result.Value.Number = a.Value.Number / b.Value.Number;
      break;
    case operator_left_bracket:
      break;
    case operator_right_bracket:
      break;
    case operator_equals:
      break;
    case operator_semicolon:break;
    case operator_colon:break;
  }
  
  return result;
}