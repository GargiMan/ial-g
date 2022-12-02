/**
 * @file graph.h
 * @author Marek Gergel (xgerge01)
 * @brief declaration of functions and variables for graph scructure access and manipulation
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "error.h"

// Limited to 62 nodes, because of cycle count implementation
#define MAX_NODE_COUNT (unsigned int)(sizeof(uint64_t) * 8) - 1
#define MAX_NODE_EDGE_COUNT (MAX_NODE_COUNT - 1)

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct node node_t;

    void graph_init();
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
