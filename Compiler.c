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

void CompilerInit(Storage *s) {
  storage = s;
}

void CompilerCompile() {
  Variable ByteLex = newVariable();
  Item *lexItem;
  
  // Compile variables
  {
    bool isReadingVariable = false;
  
    for (unsigned int i = 0; i < storage->LexStorage.Count; ++i) {
      lexItem = &storage->LexStorage.Items[i];
    
      switch (lexItem->Type) {
        case type_name: {
          Variable var;
        
          // First check if there is variable defined by user
          var = VariableFindByName(storage, lexItem->Value.Name);
          if (var.Count != 0) {
            // Rise an Redeclaration of variable error on variable redeclaration if needed
            if (
                i < storage->LexStorage.Count - 1 && // If there will be any next item
                storage->LexStorage.Items[i + 1].Type == type_operator &&
                storage->LexStorage.Items[i + 1].Value.Operator == operator_colon
                ) {
              // 27 is "Redeclaration of variable: " len
              char err[27 + MAX_VARIABLE_NAME_LEN] = "Redeclaration of variable: ";
              strcat(err, lexItem->Value.Name);
            
              DebuggerCompileError(lexItem->Line, err);
            
              continue;
            }
          
            VariableJoin(&ByteLex, &var);
            continue;
          }
        
          // Second check if there is a native variable
          var = NativeVariableGetByName(lexItem->Value.Name);
          if (var.Count != 0) {
            // Rise Overriding variable warning when overriding a native variable
            if (
                i < storage->LexStorage.Count - 1 && // If there will be any next item
                 storage->LexStorage.Items[i + 1].Type == type_operator &&
                 storage->LexStorage.Items[i + 1].Value.Operator == operator_colon
                ) {
              // 21 is "Overriding variable: " len
              char err[21 + MAX_VARIABLE_NAME_LEN] = "Overriding variable: ";
              strcat(err, lexItem->Value.Name);
  
              DebuggerWarning(lexItem->Line, err);
            }
            
            VariableJoin(&ByteLex, &var);
            continue;
          }
        
          // Unless it's the declaration of a variable report Unknown variable error
          if (!(
              i < storage->LexStorage.Count - 1 && // If there will be any next item
              storage->LexStorage.Items[i + 1].Type == type_operator &&
              storage->LexStorage.Items[i + 1].Value.Operator == operator_colon
          )) {
            // 18 is "Unknown variable: " len
            char err[18 + MAX_VARIABLE_NAME_LEN] = "Unknown variable: ";
            strcat(err, lexItem->Value.Name);
  
            DebuggerCompileError(lexItem->Line, err);
          
            continue;
          }
        
          // Create new a variable in storage
          StorageAddVariable(storage);
          (*storage->LastVariable) = newVariable();
        
          // Assign name to the variable
          storage->LastVariable->Name = (char *) malloc(strlen(lexItem->Value.Name));
          strcpy(storage->LastVariable->Name, lexItem->Value.Name);
          
          isReadingVariable = true;
        
          break;
        }
      
        default:
          // Stop reading variable at : colon
          if (lexItem->Type == type_operator &&
              lexItem->Value.Operator == operator_semicolon
              ) {
            isReadingVariable = false;
            break;
          }
          
          // If some variable is being read then
          // add item to the variable.
          if (isReadingVariable) {
            VariableAddItem(storage->LastVariable);
            (*storage->LastVariable->LastItem) = (*lexItem);
          }
            // else add item to the ByteLex
          else {
            VariableAddItem(&ByteLex);
            (*ByteLex.LastItem) = (*lexItem);
          }
        
          break;
      }
    }
  }
  
  // Clean Lex Storage
  {
    VariableClean(&storage->LexStorage);
  }
  
  // Compile equations
  {
    StorageAddByteCode(storage);
    (*storage->LastByteCode) = newVariable();
    
    for (unsigned int i = 0; i < ByteLex.Count; ++i) {
      lexItem = &ByteLex.Items[i];
    
      switch (lexItem->Type) {
        case type_nan:
          DebuggerCompileError(lexItem->Line, "Nan item");
          break;
      
        case type_number:
        case type_procedure:
          VariableAddItem(storage->LastByteCode);
          (*storage->LastByteCode->LastItem) = (*lexItem);
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
              
              VariableAddItem(storage->LastByteCode);
              (*storage->LastByteCode->LastItem) = (*lexItem);
              break;
            
            // End of equation
            case operator_equals: {
              // Convert equation to RPN
              Variable tmp = newVariable();
              EquationToRPN(storage->LastByteCode, &tmp);
              (*storage->LastByteCode) = tmp;
            
              // Start a new equation
              if (i != ByteLex.Count - 1) {
                StorageAddByteCode(storage);
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