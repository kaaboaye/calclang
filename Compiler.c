//
// Created by Mieszko Wawrzyniak on 05/12/2017.
//

#include "Compiler.h"
#include "Storage.h"
#include "Variable.h"
#include "Item.h"
#include "ItemValue.h"
#include "Equation.h"
#include "NativeVariables.h"
#include "Debugger.h"

/**
 * Sets up static variables in
 * @param s
 */
Compiler newCompiler(Storage *s) {
  Compiler c;
  
  c.storage = s;
  
  return c;
}

/**
 * Compiles Lex output to the byte code
 * @param c Compiler object
 */
void CompilerCompile(Compiler *c) {
  Variable ByteLex = newVariable();
  Item *lexItem;
  
  CompileVariables(c, &c->storage->LexStorage, &ByteLex);
  
  // Clean Lex Storage
  {
    VariableClean(&c->storage->LexStorage);
  }
  
  // Compile equations
  {
    StorageAddByteCode(c->storage);
    (*c->storage->LastByteCode) = newVariable();
    
    for (unsigned int i = 0; i < ByteLex.Count; ++i) {
      lexItem = &ByteLex.Items[i];
    
      switch (lexItem->Type) {
        case type_nan:
          DebuggerCompileError(lexItem->Line, "Nan item");
          break;
      
        case type_number:
        case type_procedure:
          VariableAddItem(c->storage->LastByteCode);
          (*c->storage->LastByteCode->LastItem) = (*lexItem);
          break;
      
        case type_operator:
          switch (lexItem->Value.Operator) {
            // Add to equation
            case operator_addition:
            case operator_subtraction:
            case operator_multiplication:
            case operator_division:
            case operator_left_bracket:
            case operator_right_bracket:
              
              VariableAddItem(c->storage->LastByteCode);
              (*c->storage->LastByteCode->LastItem) = (*lexItem);
              break;
            
            // End of equation
            case operator_equals: {
              // Convert equation to RPN
              Variable tmp = newVariable();
              EquationToRPN(c->storage->LastByteCode, &tmp);
              (*c->storage->LastByteCode) = tmp;
            
              // Start a new equation
              if (i != ByteLex.Count - 1) {
                StorageAddByteCode(c->storage);
                (*c->storage->LastByteCode) = newVariable();
              }
  
              break;
            }
            
            case operator_colon:break;
            case operator_semicolon:break;
          }
          break;
      
        case type_name: break;
      }
    }
  }
}

/**
 * Handles Variables compilation
 * @param c Compiler object
 * @param in Input Lex array
 * @param out Output ByteCode array
 */
void CompileVariables(Compiler *c, Variable *in, Variable *out) {
  Item *lexItem;
  bool isReadingVariable = false;
  
  for (unsigned int i = 0; i < in->Count; ++i) {
    lexItem = &in->Items[i];
    
    if (!isReadingVariable &&
        lexItem->Type == type_name) {
      
      Variable var;
      
      // First check if there is variable defined by user
      var = VariableFindByName(c->storage, lexItem->Value.Name);
      if (var.Count != 0) {
        // Rise an Redeclaration of variable error on variable redeclaration if needed
        if (
            i < in->Count - 1 && // If there will be any next item
            in->Items[i + 1].Type == type_operator &&
            in->Items[i + 1].Value.Operator == operator_colon
            ) {
          // 27 is "Redeclaration of variable: " len
          char err[27 + MAX_VARIABLE_NAME_LEN] = "Redeclaration of variable: ";
          strcat(err, lexItem->Value.Name);
          
          DebuggerCompileError(lexItem->Line, err);
          
          continue;
        }
        
        Variable tmpVar = newVariable();
        CompileVariables(c, &var, &tmpVar);
        VariableJoin(out, &tmpVar);
        continue;
      }
      
      // Second check if there is a native variable
      var = NativeVariableGetByName(lexItem->Value.Name);
      if (var.Count != 0) {
        // Rise Overriding variable warning when overriding a native variable
        if (
            i < in->Count - 1 && // If there will be any next item
            in->Items[i + 1].Type == type_operator &&
            in->Items[i + 1].Value.Operator == operator_colon
            ) {
          // 28 is "Overriding native variable: " len
          char err[28 + MAX_VARIABLE_NAME_LEN] = "Overriding native variable: ";
          strcat(err, lexItem->Value.Name);
          
          DebuggerWarning(lexItem->Line, err);
        }
  
        Variable tmpVar = newVariable();
        CompileVariables(c, &var, &tmpVar);
        VariableJoin(out, &tmpVar);
        continue;
      }
      
      // Unless it's the declaration of a variable report Unknown variable error
      if (!(
          i < c->storage->LexStorage.Count - 1 && // If there will be any next item
          c->storage->LexStorage.Items[i + 1].Type == type_operator &&
          c->storage->LexStorage.Items[i + 1].Value.Operator == operator_colon
      )) {
        // 18 is "Unknown variable: " len
        char err[18 + MAX_VARIABLE_NAME_LEN] = "Unknown variable: ";
        strcat(err, lexItem->Value.Name);
        
        DebuggerCompileError(lexItem->Line, err);
        
        continue;
      }
      
      // Create new a variable in storage
      StorageAddVariable(c->storage);
      (*c->storage->LastVariable) = newVariable();
      
      // Assign name to the variable
      c->storage->LastVariable->Name = (char *) malloc(strlen(lexItem->Value.Name));
      strcpy(c->storage->LastVariable->Name, lexItem->Value.Name);
      
      isReadingVariable = true;
      continue;
    }
    
    // Stop reading variable at : colon
    if (lexItem->Type == type_operator &&
        lexItem->Value.Operator == operator_semicolon
        ) {
      isReadingVariable = false;
      continue;
    }
    
    // Skip the : colon operator
    if (lexItem->Type == type_operator &&
        lexItem->Value.Operator == operator_colon) {
      continue;
    }
    
    // If some variable is being read then
    // add item to the variable.
    if (isReadingVariable) {
      VariableAddItem(c->storage->LastVariable);
      (*c->storage->LastVariable->LastItem) = (*lexItem);
    }
      // else add item to the ByteLex
    else {
      VariableAddItem(out);
      (*out->LastItem) = (*lexItem);
    }
  }
}