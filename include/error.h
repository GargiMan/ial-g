/**
 * @file error.h
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "resources.h"

typedef enum errorCodes {
    parserSyntaxError = 1,
    parserNodeCountZeroError = 2,
    parserNodeCountOverflowError = 3,
    parserNodeNameLengthOverflowError = 4,
    graphNodeNameDuplicationError = 5,
    graphNodeNameNotFoundError = 6,
    graphNodeEdgeLoopError = 7,
    internalError = 99
} errorCodes_t;

void error_exit(errorCodes_t errcode, char* msg, ...);
void warning_print(char* msg, ...);

#endif // ERROR_H