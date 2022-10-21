/**
 * @file main.c
 * @author All (replace)
 * @brief Main program function
 *
 */
#include "../include/parser.h"
#include "../include/graph.h"
#include "../include/resources.h"
#include <stdio.h>

/**
 * @brief Program reads unoriented graph from stdin and analyze it's properties
 * 
 * @return int exit code
 */ 
int main() {

    parse_data(stdin);

    //graph_analyze_properties();

    FREE_RESOURCES;

    return 0;
}
