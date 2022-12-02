/**
 * @file main.c
 * @author Marek Gergel (xgerge01)
 * @brief definition of main function and program print help function
 * @version 0.1
 * @date 2022-10-26
 *
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
    printf("Run example (from project dir): ./graph_properties < testData/graphComplete\n");
}

/**
 * @brief Program reads unoriented graph from stdin and analyze it's properties
 * @return int exit code
 */
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // ignore unused parameter warning
        (void)argv;

        print_help();
        return 0;
    }

    parse_data(stdin);

    graph_analyze_properties();

    FREE_RESOURCES;

    return 0;
}
