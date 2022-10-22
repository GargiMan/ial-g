/**
 * @file parser.h
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"
#include "error.h"

#define MAX_NODE_NAME_LENGTH 256

void parse_data(FILE* stream);

#endif // PARSER_H