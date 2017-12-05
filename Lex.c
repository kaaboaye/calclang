//
// Created by Mieszko Wawrzyniak on 02/12/2017.
//

#include "Lex.h"
#include "Storage.h"
#include "Variable.h"
#include "Item.h"
#include "ItemValue.h"
#include "NativeVariables.h"

void LexInit(Storage *s, FILE *in) {
  NativeVariablesInit();
  storage = s;
  s->LexStorage = newVariable();
  input = in;
  isReadingComment = false;
}

bool LexUpdate() {
  int c;
  
  // Read character
  if (EOF == (c = DebuggerGetC(input))) {
    return false; // break;
  }
  
  // Ignore comments
  if (!isReadingComment && c == '#') {
    isReadingComment = true;
    return true;
  }

  if (isReadingComment && c != '\n') {
    return true;
  }
  
  if (isReadingComment && c == '\n') {
    isReadingComment = false;
    return true;
  }
  
  // Ignore whitespaces
  if (isspace(c)) {
    return true;
  }
  
  // Read item
  {
    DebuggerUnGetC
        (c, input);
    
    Item tmpItem;
    ReadItem(&tmpItem, input);
    
    VariableAddItem(&storage->LexStorage);
    (*storage->LexStorage.LastItem) = tmpItem;
    
    return true;
  }
}