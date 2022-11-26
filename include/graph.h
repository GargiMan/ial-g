/**
 * @file graph.h
 * @author Marek Gergel (xgerge01)
 * @brief
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
#define MAX_EDGE_COUNT (MAX_NODE_COUNT - 1)

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct node node_t;

    struct node
    {
        char *name;
        unsigned int edge_count;
        node_t *edge_nodes[MAX_EDGE_COUNT];
    };

    typedef struct graph
    {
        unsigned int node_count;
        node_t *nodes[MAX_NODE_COUNT];
    } graph_t;

    extern struct node root_node_t;
    extern struct graph root_graph_t;
    extern graph_t *graph; // Make graph static

    void graph_init();
    void graph_destroy();
    void graph_create_node(char *nodeName);
    void graph_create_edge(char *nodeName, char *node2Name);
    unsigned int graph_get_node_count();
    unsigned int graph_get_edge_count();
    unsigned int node_get_edge_count(char *nodeName);

#ifdef __cplusplus
}
#endif
#endif // GRAPH_H
