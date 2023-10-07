#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
//#include "error.h"


#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct node node_t;

    bool** graph_init(int node_cnt);
    void graph_destroy();
    void graph_create_node(char *nodeName);
    void graph_create_edge(char *nodeName, char *node2Name);
    unsigned int graph_get_node_count();
    node_t *graph_get_node_by_index(unsigned int nodeIndex);
    unsigned int node_get_edge_count(node_t *node);
    node_t *node_get_edge_node_by_index(node_t *node, unsigned int edgeNodeIndex);
    unsigned int graph_get_node_index(node_t *node);

#ifdef __cplusplus
}
#endif
#endif // GRAPH_H
