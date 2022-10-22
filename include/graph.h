/**
 * @file graph.h
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <string.h>
#include "error.h"

#define MAX_NODE_COUNT 256

void graph_init();
void graph_destroy();
void graph_create_node(char* nodeName);
void graph_create_edge(char* nodeName, char* node2Name);
int graph_get_node_count();
int node_get_edge_count(char* nodeName);

#endif // GRAPH_H