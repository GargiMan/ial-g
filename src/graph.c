/**
 * @file graph.c
 * @author Marek Gergel (xgerge01)
 * @brief definition of functions and variables for graph scructure access and manipulation
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/graph.h"

struct node
{
    unsigned int index;
    unsigned int edge_count;
    node_t **edge_nodes;
};

typedef struct graph
{
    unsigned int node_count;
    node_t **nodes;
} graph_t;

graph_t *graph = NULL;

/**
 * @brief Internal allocation function with zeroing and error checking.
 * In case of error exits the program with error code internalError.
 * @param n number of elements to allocate
 * @param size size of each element
 * @return void* pointer to the allocated memory
 */
void *alloc(size_t n, size_t size)
{
    void *ptr = calloc(n, size);
    if (!ptr)
    {
        error_exit(internalError, "Memory allocation failed\n");
    }
    return ptr;
}

/**
 * @brief Internal reallocation function with error checking.
 * In case of error exits the program with error code internalError.
 * @param prevPtr void* pointer to the allocated memory
 * @param size total size with allocated memotry
 * @return void* pointer to the reallocated memory
 */
void *re_alloc(void* prevPtr, size_t size)
{
    void *ptr = realloc(prevPtr, size);
    if (!ptr)
    {
        error_exit(internalError, "Memory reallocation failed\n");
    }
    return ptr;
}

/**
 * @brief Function creates a new graph and set the number of nodes to 0.
 */
void graph_init()
{
    if (graph)
    {
        error_exit(internalError, "Graph was already initialized\n");
    }
    graph = (graph_t *)alloc(1, sizeof(graph_t));
    graph->nodes = NULL;
    graph->node_count = 0;
}

/**
 * @brief Function destroys the graph.
 */
void graph_destroy()
{
    if (!graph)
    {
        return;
    }
    for (unsigned int i = 0; i < graph->node_count; i++)
    {
        free(graph->nodes[i]->edge_nodes[i]);
        free(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);
}

/**
 * @brief Function creates a new node in graph.
 * @throw Error when graph is full (max nodes created) or node with same name already exist.
 * @param nodeIndex index of the node
 */
void graph_create_node(unsigned int nodeIndex)
{   
    node_t *node = (node_t *)alloc(1, sizeof(node_t));
    node->index = nodeIndex;
    node->edge_count = 0;
    node->edge_nodes = NULL;

    if (graph->node_count % 10 == 0) {
        graph->nodes = re_alloc(graph->nodes, (graph->node_count + 10) * sizeof(node_t *));
    }

    graph->nodes[graph->node_count++] = node;
}

/**
 * @brief Function creates a new edge between 2 nodes in graph.
 * @param nodeIndex index of the node
 * @param node2Index index of the node2
 */
void graph_create_edge(unsigned int nodeIndex, unsigned int node2Index)
{
    if (nodeIndex == node2Index)
    {
        error_exit(graphNodeEdgeLoopError, "Node '%d' cannot have an edge to itself\n", nodeIndex);
    }

    node_t *node = graph_get_node_by_index(nodeIndex);
    node_t *node2 = graph_get_node_by_index(node2Index);

    for (unsigned int i = 0; i < node->edge_count; i++)
    {
        if (node->edge_nodes[i] == node2)
        {
            warning_print("Edge (%d,%d) already exists, edges (%d,%d) and (%d,%d) are equal\n", nodeIndex, node2Index, nodeIndex, node2Index, node2Index, nodeIndex);
            return;
        }
    }

    if (node->edge_count % 10 == 0) {
        node->edge_nodes = re_alloc(node->edge_nodes, (node->edge_count + 10) * sizeof(node_t *));
    }
    node->edge_nodes[node->edge_count++] = node2;

    if (node2->edge_count % 10 == 0) {
        node2->edge_nodes = re_alloc(node2->edge_nodes, (node2->edge_count + 10) * sizeof(node_t *));
    }
    node2->edge_nodes[node2->edge_count++] = node;
}

/**
 * @brief Functions returns count of all nodes in graph
 * @return int node count
 */
unsigned int graph_get_node_count()
{
    return graph->node_count;
}

/**
 * @brief Function returns node structure by its index.
 * @param nodeIndex name of the node
 * @return node_t* node structure pointer
 */
node_t *graph_get_node_by_index(unsigned int nodeIndex)
{
    if (nodeIndex >= graph->node_count)
    {
        error_exit(graphNodeNotFoundError, "Node index out of range\n");
    }

    return graph->nodes[nodeIndex];
}

/**
 * @brief Function returns node structure of the edge connected node by index
 * @param node node structure pointer
 * @param edgeNodeIndex index of the edge node
 * @return node_t* node structure pointer
 */
node_t *node_get_edge_node_by_index(node_t *node, unsigned int edgeNodeIndex)
{
    return node->edge_nodes[edgeNodeIndex];
}

/**
 * @brief Function returns count of all edges connected to node
 * @param node node structure pointer
 * @return int edge count
 */
unsigned int node_get_edge_count(node_t *node)
{
    return node->edge_count;
}

/**
 * @brief Get node index in graph
 * @param node node structure pointer
 * @return index of node in graph->nodes array
 */
unsigned int node_get_index(node_t *node)
{
    return node->index;
}
