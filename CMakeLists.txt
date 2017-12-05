cmake_minimum_required(VERSION 3.9)
project(calclang C)

set(CMAKE_C_STANDARD 99)

add_executable(calclang ItemType.c ItemType.h ItemValue.c ItemValue.h Item.c Item.h Variable.c Variable.h Operator.c Operator.h Lex.c Lex.h Storage.c Storage.h Main.c Debugger.c Debugger.h Equation.c Equation.h ItemsStack.c ItemsStack.h MathHelpers.c MathHelpers.h NativeVariables.c NativeVariables.h Compiler.c Compiler.h Runtime.c Runtime.h ExitCodes.h)