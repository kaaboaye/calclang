//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include "Lex.h"
#include "Storage.h"
#include "Variable.h"
#include "Item.h"
#include "ItemValue.h"

void LexStart(Storage *s, FILE *in) {
  root = newVariable();
  storage = s;
  input = in;
}

bool LexUpdate() {
  int c;
  
  // Read character
  if (EOF == (c = fgetc(input))) {
    return false;
  }
  
  // Detect newline
  if (c == '\n') {
    DebuggerWasNewLine();
    return true;
  }
  
  // Ignore whitespaces
  if (isspace(c)) {
    return true;
  }
  
  // Read variable
//  if (isalpha(c)) {
//    ungetc(c, input);
//
//    Variable var = newVariable();
//    ReadVariable(&var, input);
//  }
  
  // Read item
  {
    ungetc(c, input);
    
    Item item;
    
    ReadItem(&item, input);
  
    switch (item.Type){
      case type_int:
        printf("Int: %d\n", item.Value.Int);
        break;
      case type_float:
        printf("Float: %Lf\n", item.Value.Float);
        break;
      case type_operator:
        switch (item.Value.Operator) {
          case operator_addition:
            puts("Addition");
            break;
          case operator_subtraction:
            puts("Subtraction");
            break;
          case operator_equals:
            puts("Equals");
            break;
        }
        break;
    }
    
    VariableAddItem(&root);
    (*root.LastItem) = item;
    return true;
  }
}