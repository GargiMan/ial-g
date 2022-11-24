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
 * @brief Print program help message
 */
void print_help()
{
    printf("Program reads unoriented graph from stdin and analyze and print it's properties to stdout in formated output\n");
    printf("This help message is printed when program run contains argument.\n");
    printf("Run example (from project dir): ./graph_analyzer < testData/graph1\n");
}

/**
 * @brief Program reads unoriented graph from stdin and analyze it's properties
 * @return int exit code
 */
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        print_help();
        return 0;
    }

    parse_data(stdin);

    graph_analyze_properties();

    FREE_RESOURCES;

    return 0;
}
