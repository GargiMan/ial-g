/**
 * @file error.h
 * @author Marek Gergel (xgerge01)
 * @brief
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "resources.h"
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum errorCodes
    {
        parserSyntaxError = 1,
        parserNodeCountZeroError = 2,
        parserNodeCountOverflowError = 3,
        parserNodeNameLengthOverflowError = 4,
        graphNodeNameDuplicationError = 5,
        graphNodeNameNotFoundError = 6,
        graphNodeEdgeLoopError = 7,
        internalError = 99
    } errorCodes_t;

    void error_exit(errorCodes_t errcode, char *msg, ...);
    void warning_print(char *msg, ...);
#ifdef __cplusplus
}
#endif
#endif // ERROR_H
