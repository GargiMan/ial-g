/**
 * @file error.h
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#ifndef ERROR_H
#define ERROR_H

typedef enum errorCodes {
    graphSyntaxError = 1,
    graphNodeCountZeroError = 2,
    graphNodeCountOverflowError = 3,
    graphNodeNameDuplicationError = 4,
    graphNodeNameNotFoundError = 5,
    nodeEdgeLoopError = 6,
    forbiddenOperationError = 98,
    internalError = 99,
} errorCodes_t;

void error_exit(errorCodes_t errcode, char* msg, ...);
void warning_print(char* msg, ...);

#endif // ERROR_H