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
#define MAX_EDGE_COUNT (MAX_NODE_COUNT - 1)

typedef struct node node_t;

struct node {
    char* name;
    int edge_count;
    node_t* edge_nodes[MAX_EDGE_COUNT];
};

typedef struct graph {
    int node_count;
    node_t* nodes[MAX_NODE_COUNT];
} graph_t;

extern struct node root_node_t;
extern struct graph root_graph_t;

void graph_init();
void graph_destroy();
void graph_create_node(char* nodeName);
void graph_create_edge(char* nodeName, char* node2Name);
int graph_get_node_count();
int graph_get_edge_count();
int node_get_edge_count(char* nodeName);

#endif // GRAPH_H
