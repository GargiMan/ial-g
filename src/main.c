/**
 * @file main.c
 * @authors Marek Gergel (xgerge01), Jindřich Šíma (xsimaj04) + Others(replace)
 * @brief declaration of functions for graph analysis and their subsequent execution
 * @version 0.1
 * @date 2022-10-26
 * @todo add names of others members
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include "../include/parser.h"
#include "../include/graph_properties.h"
#include "../include/resources.h"

/**
 * @brief Program reads unoriented graph from stdin and analyze it's properties
 * @return int exit code
 */
int main()
{

    parse_data(stdin);

    graph_analyze_properties();

    FREE_RESOURCES;

    return 0;
}
