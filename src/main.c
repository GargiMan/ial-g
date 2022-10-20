/**
 * @file main.c
 * @author All (replace)
 * @brief Program reads unoriented graph from stdin and analyze it's properties
 *
 */
#include <stdio.h>
#include "../include/parser.h"
#include "../include/graph.h"
#include "../include/resources.h"

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */ 
int main() {

    parse_data(stdin);

    //graph_analyze_properties();

    FREE_RESOURCES;

    return 0;
}
