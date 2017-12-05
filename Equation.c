//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#include "Equation.h"
#include "Variable.h"
#include "Item.h"
#include "ItemsStack.h"
#include "ItemValue.h"
#include "Debugger.h"

void EquationInit() {
  equationAns = 0.0;
}

Item EquationSolve(const Variable *in) {
  Variable rpn = newVariable();
  EquationToRPN(in, &rpn);
  return EquationRPNSolve(&rpn);
}

Item EquationRPNSolve(const Variable *in) {
  ItemsStack stack = newItemsStack();
  Item result;
  Item a;
  Item b;
  
  for (unsigned int i = 0; i < in->Count; ++i) {
    switch (in->Items[i].Type) {
      case type_procedure: {
        Item item;
        item.Type = type_number;
        item.Value.Number = in->Items[i].Value.Procedure();
        
        ItemsStackPush(&stack, item);
        break;
      }
      case type_number:
        ItemsStackPush(&stack, in->Items[i]);
        break;
      case type_operator:
        // Try to get 2 numbers from the stack
        if (
            !(
              ItemsStackPop(&stack, &a) &&
              ItemsStackPop(&stack, &b)
            )
        ) {
          DebuggerSyntaxError(in->Items[i].Line, "Wrong equation");
        }
        
        ItemsStackPush(&stack, ItemCalc(a, in->Items[i], b));
        break;
      case type_nan:break;
      case type_name:break;
    }
  }
  
  ItemsStackPop(&stack, &result);
  equationAns = result.Value.Number;
  
  return result;
}

void EquationToRPN(const Variable *in, Variable *out) {
  ItemsStack stack = newItemsStack();
  
  for (unsigned int i = 0; i < in->Count; ++i) {
    switch (in->Items[i].Type) {
      case type_number:
      case type_procedure:
        VariableAddItem(out);
        (*out->LastItem) = in->Items[i];
        break;
  
      case type_operator:
        // Left bracket
        if (in->Items[i].Value.Operator == operator_left_bracket) {
          ItemsStackPush(&stack, in->Items[i]);
          continue;
        }
        
        // Right bracket
        if (in->Items[i].Value.Operator == operator_right_bracket) {
          while (stack.TopItem->Value.Operator != operator_left_bracket) {
            // Pop operators from the operator stack, onto the output queue.
            VariableAddItem(out);
            if (!ItemsStackPop(&stack, out->LastItem)) {
              DebuggerSyntaxError(in->Items[i].Line, "Missing '(' left bracket");
              break;
            }
          }
          
          { // Pop the left bracket from the stack.
            Item nullItem;
            ItemsStackPop(&stack, &nullItem);
          }
        }
        
        // Equals
        if (in->Items[i].Value.Operator == operator_equals) {
          continue;
        }
        
        while (
            (stack.Count > 0) &&
            (OperatorsCompare(stack.TopItem->Value.Operator, in->Items[i].Value.Operator) > 0)
        ) {
          // Pop operators from the operator stack, onto the output queue.
          VariableAddItem(out);
          if (!ItemsStackPop(&stack, out->LastItem)) {
            break;
          }
        }
        
        // Push the read operator onto the operator stack.
        ItemsStackPush(&stack, in->Items[i]);
        break;
      case type_nan:break;
      case type_name:break;
    }
  }
  
  if (stack.Count > 0 && (
      stack.TopItem->Value.Operator == operator_left_bracket ||
      stack.TopItem->Value.Operator == operator_right_bracket)) {
    DebuggerSyntaxError(in->LastItem->Line, "Incorrect brackets");
  }
  
  Item item;
  while (ItemsStackPop(&stack, &item)) {
    
    VariableAddItem(out);
    (*out->LastItem) = item;
  }
}

long double EquationGetAns() {
  return equationAns;
}