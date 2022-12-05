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
    char *name;
    unsigned int edge_count;
    node_t *edge_nodes[MAX_NODE_EDGE_COUNT];
};

typedef struct graph
{
    unsigned int node_count;
    node_t *nodes[MAX_NODE_COUNT];
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
 * @brief Function creates a new graph and set the number of nodes to 0.
 */
void graph_init()
{
    if (graph)
    {
        error_exit(internalError, "Graph was already initialized\n");
    }
    graph = (graph_t *)alloc(1, sizeof(graph_t));
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
        free(graph->nodes[i]->name);
        free(graph->nodes[i]);
    }
    free(graph);
}

/**
 * @brief Function creates a new node in graph.
 * @throw Error when graph is full (max nodes created) or node with same name already exist.
 * @param nodeName name of the node
 */
void graph_create_node(char *nodeName)
{
    if (graph->node_count >= MAX_NODE_COUNT)
    {
        error_exit(parserNodeCountOverflowError, "Node limit reached (%i)\n", MAX_NODE_COUNT);
    }
    for (unsigned int i = 0; i < graph->node_count; i++)
    {
        if (strcmp(graph->nodes[i]->name, nodeName) == 0)
        {
            error_exit(graphNodeNameDuplicationError, "Node with name '%s' already exists\n", nodeName);
        }
    }

    node_t *node = (node_t *)alloc(1, sizeof(node_t));
    node->name = (char *)alloc(strlen(nodeName) + 1, sizeof(char));
    strcpy(node->name, nodeName);
    node->edge_count = 0;
    graph->nodes[graph->node_count++] = node;
}

/**
 * @brief Function returns node structure by its name.
 * @param nodeName name of the node
 * @return node_t* node structure pointer
 */
node_t *graph_get_node_by_name(char *nodeName)
{
    for (unsigned int i = 0; i < graph->node_count; i++)
    {
        if (strcmp(graph->nodes[i]->name, nodeName) == 0)
        {
            return graph->nodes[i];
        }
    }
    error_exit(graphNodeNotFoundError, "Node with name '%s' not found\n", nodeName);
    return NULL;
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
 * @brief Function creates a new edge between 2 nodes in graph.
 * @param nodeName name of the first node
 * @param node2Name name of the second node
 */
void graph_create_edge(char *nodeName, char *node2Name)
{
    if (strcmp(nodeName, node2Name) == 0)
    {
        error_exit(graphNodeEdgeLoopError, "Node '%s' cannot have an edge to itself\n", nodeName);
    }
    node_t *node = graph_get_node_by_name(nodeName);
    node_t *node2 = graph_get_node_by_name(node2Name);
    for (unsigned int i = 0; i < node->edge_count; i++)
    {
        if (node->edge_nodes[i] == node2)
        {
            warning_print("Edge (%s,%s) already exists, edges (%s,%s) and (%s,%s) are equal\n", nodeName, node2Name, nodeName, node2Name, node2Name, nodeName);
            return;
        }
    }
    node->edge_nodes[node->edge_count++] = node2;
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
 * @return int node count
 */
unsigned int node_get_edge_count(node_t *node)
{
    return node->edge_count;
}

/**
 * @brief Get node index in graph
 * @param node node to be searched
 * @return index of node in graph->nodes array
 */
unsigned int graph_get_node_index(node_t *node)
{
    unsigned int node_count = graph_get_node_count();

    for (unsigned int i = 0; i < node_count; i++)
    {
        if (graph_get_node_by_index(i) == node)
        {
            return i;
        }
    }
    return 0;
}
