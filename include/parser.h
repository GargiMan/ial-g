/**
 * @file parser.h
 * @author Marek Gergel (xgerge01)
 * @brief declaration of functions and variables for parsing input with graph data
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"
#include "error.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void parse_data(FILE *stream);

#ifdef __cplusplus
}
#endif
#endif // PARSER_H
