//
// Created by Mieszko Wawrzyniak on 03/12/2017.
//

#ifndef CALCLANG_VARIABLENAME_H
#define CALCLANG_VARIABLENAME_H

#define VAR_INTERNAL -1
#define VAR_UNNAMED -2

typedef struct {
  int Id;
  unsigned char *Name;
} VariableName;

#endif //CALCLANG_VARIABLENAME_H
