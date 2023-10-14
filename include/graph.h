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

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct node node_t;

    void graph_init();
    void graph_destroy();
    void graph_create_node(unsigned int index);
    void graph_create_edge(unsigned int nodeIndex, unsigned int node2Index);
    unsigned int graph_get_node_count();
    node_t *graph_get_node_by_index(unsigned int nodeIndex);
    node_t *node_get_edge_node_by_index(node_t *node, unsigned int edgeNodeIndex);
    unsigned int node_get_edge_count(node_t *node);
    unsigned int node_get_index(node_t *node);

#ifdef __cplusplus
}
#endif
#endif // GRAPH_H
