/**
 * @file graph.c
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#include "../include/graph.h"


graph_t* graph;

int number_of_edges=0;

/**
 * @brief Internal allocation function with zeroing and error checking.
 * In case of error exits the program with error code internalError.
 * 
 * @param n number of elements to allocate
 * @param size size of each element
 * @return void* pointer to the allocated memory
 */
void* alloc(size_t n, size_t size) {
    void* ptr = calloc(n, size);
    if (!ptr) {
        error_exit(internalError, "Memory allocation failed\n");
    }
    return ptr;
}

void graph_init() {
    graph = (graph_t*)alloc(1, sizeof(graph_t));
    graph->node_count = 0;
}

void graph_destroy() {
    if (!graph) return; 
    for (int i = 0; i < graph->node_count; i++) {
        free(graph->nodes[i]->name);
        free(graph->nodes[i]);
    }
    free(graph);
}

void graph_create_node(char* nodeName) {
    if (graph->node_count >= MAX_NODE_COUNT) {
        error_exit(parserNodeCountOverflowError, "Node limit reached (%i)\n", MAX_NODE_COUNT);
    }
    for (int i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->name, nodeName) == 0) {
            error_exit(graphNodeNameDuplicationError, "Node with name '%s' already exists\n", nodeName);
        }
    }

    node_t* node = (node_t*)alloc(1, sizeof(node_t));
    node->name = (char *)alloc(strlen(nodeName) + 1, sizeof(char));
    strcpy(node->name, nodeName);
    node->edge_count = 0;
    graph->nodes[graph->node_count++] = node;
}

node_t* graph_get_node(char* nodeName) {
    for (int i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->name, nodeName) == 0) {
            return graph->nodes[i];
        }
    }
    error_exit(graphNodeNameNotFoundError, "Node with name '%s' not found\n", nodeName);
    return NULL;
}

void graph_create_edge(char* nodeName, char* node2Name) {
    if (strcmp(nodeName, node2Name) == 0) {
        error_exit(graphNodeEdgeLoopError, "Node '%s' cannot have an edge to itself\n", nodeName);
    }
    node_t* node = graph_get_node(nodeName);
    node_t* node2 = graph_get_node(node2Name);
    for (int i = 0; i < node->edge_count; i++) {
        if (node->edge_nodes[i] == node2) {
            warning_print("Edge (%s,%s) == (%s,%s) already exists\n", nodeName, node2Name, node2Name, nodeName);
            return;
        }
    }
    node->edge_nodes[node->edge_count++] = node2;
    node2->edge_nodes[node2->edge_count++] = node;
    number_of_edges+=1;
}

int graph_get_node_count() {
    return graph->node_count;
}

int graph_get_edge_count() {
    return number_of_edges;
}

int node_get_edge_count(char* nodeName) {
    return (graph_get_node(nodeName))->edge_count;
}

