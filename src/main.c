/**
 * @file main.c
 * @author All (replace)
 * @brief Main program function
 */

#include <stdio.h>
#include "../include/parser.h"
#include "../include/graph_properties.h"
#include "../include/resources.h"

/**
 * @brief Program reads unoriented graph from stdin and analyze it's properties
 * 
 * @return int exit code
 */ 
int main() {

    parse_data(stdin);

    graph_analyze_properties();

    FREE_RESOURCES;

    return 0;
}
