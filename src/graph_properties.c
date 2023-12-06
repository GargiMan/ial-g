/**
 * @file graph_properties.c
 * @authors Marek Gergel (xgerge01), Lukáš Kysela (xkysel16), Daniel jacobs (xjacob00), Jakub Pekárek (xpekar19)
 * @brief definition of functions and variables for graph analysis and their subsequent execution,
 * time complexity description (|V| = number of vertices (nodes), |E| = number of edges)
 * @version 0.2
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/graph_properties.h"
#include <time.h>

clock_t begin, end;

void timer_start()
{
	begin = clock();
}

void timer_stop()
{
	end = clock();
}

void timer_print()
{
	printf("\t\truntime: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

void* mem_alloc(size_t num, size_t size) 
{
    void* ptr = malloc(num * size);
    if (!ptr) {
    	error_exit(internalError, "Memory allocation failed\n");
    }
    return ptr;
}

int compare(const void * a, const void * b) {
	return (*(unsigned int*)a - *(unsigned int*)b);
}

/**
 * @brief normalize cycle
 *
 * Time complexity: O(|V|)
 * @param cycle array of cycle
 * @param path_len length of path
 */
void normalize_cycle(unsigned int* cycle, unsigned int path_len) {
    unsigned int min_index = 0;

    for (unsigned int i = 1; i < path_len; i++) {
        if (cycle[i] < cycle[min_index]) {
            min_index = i;
        }
    }

    unsigned int* tmp = mem_alloc(path_len, sizeof(unsigned int));
    memcpy(tmp, cycle, path_len * sizeof(unsigned int));

    for (unsigned int i = 0; i < path_len; i++) {
        cycle[i] = tmp[(min_index + i) % path_len];
    }

    free(tmp);
}

/**
 * @brief Depth first search function
 *  It goes through all neighbors of the inserted nodes,
 *  if any of them has already been checked, it skips,
 *  otherwise the selected one is called recursively until all nodes are checked
 * @param node node to be searched
 * @param visited bit array of visited nodes
 */
void depth_first_search(node_t *node, bool *visited)
{
    unsigned int node_index = node_get_index(node);

    // Mark the current node as visited
    visited[node_index - 1] = true;

    // Explore all unvisited neighbors
    for (unsigned int i = 0; i < node_get_edge_count(node); i++)
    {
        node_t *neighbor = node_get_edge_node_by_index(node, i);
        unsigned int neighbor_index = node_get_index(neighbor);

        if (!visited[neighbor_index - 1])
        {
            depth_first_search(neighbor, visited);
        }
    }
}

/**
 * @brief deep-first search function to determine if the graph is continuous
 *
 * Time complexity: O(|V|+|E|)
 * @param visited bit array of visited nodes
 * @param path array of visited nodes
 * @param path_len length of path
 * @param node_index index of node
 * @param cycle_start_node_index index of cycle start node
 * @param cycle_count count of cycles
 * @param node_count count of nodes
 * @param unique_cycles array of unique cycles
 */
void depth_first_search_cycle(bool* visited, unsigned int* path, unsigned int path_len, unsigned int node_index, unsigned int cycle_start_node_index, unsigned int* cycle_count, unsigned int node_count, unsigned int** unique_cycles) {
    visited[node_index - 1] = true;
    path[path_len] = node_index;

    for (unsigned int i = 0; i < node_get_edge_count(graph_get_node_by_index(node_index)); i++) {
        node_t* neighbor = node_get_edge_node_by_index(graph_get_node_by_index(node_index), i);
        unsigned int neighbor_index = node_get_index(neighbor);

        if (visited[neighbor_index - 1]) {
            if (neighbor_index == cycle_start_node_index && path_len >= 2) {
                unsigned int* cycle = mem_alloc(path_len +2, sizeof(unsigned int));
				normalize_cycle(cycle, path_len + 1);
				memcpy(cycle, path, (path_len + 1) * sizeof(unsigned int));
                qsort(cycle, path_len + 1, sizeof(unsigned int), compare);
				

                bool is_unique = true;
				
                for (unsigned int i = 0; i < *cycle_count; i++) {
                    if (memcmp(unique_cycles[i], cycle, (path_len + 1) * sizeof(unsigned int)) == 0) {
                        is_unique = false;
                        break;
                    }
                }

                if (is_unique) {
			    	unique_cycles[*cycle_count] = cycle;

			    	if (is_unique) {
			    	    (*cycle_count)++;
			    	} else {
			    	    free(cycle);
			    	}
				}
            }
        }
        else if (path_len + 1 < node_count) {
            depth_first_search_cycle(visited, path, path_len + 1, neighbor_index, cycle_start_node_index, cycle_count, node_count, unique_cycles);
        }
    }

    visited[node_index - 1] = false;
}

/**
 * @brief deep-first search function to determine if the graph is continuous
 *
 * Time complexity: O(|V|+|E|)
 * @return bool graph is connected
 */
bool graph_is_connected() {
    timer_start();

    unsigned int node_count = graph_get_node_count();
    bool *visited = mem_alloc(node_count, sizeof(bool));
	memset(visited, 0, node_count * sizeof(bool));

    depth_first_search(graph_get_node_by_index(1), visited);

    for (unsigned int i = 0; i < node_count; i++) {
        if (!visited[i]) {
            timer_stop();
            free(visited);
            return false;
        }
    }

    timer_stop();
    free(visited);
    return true;
}

/**
 * @brief Loops through all nodes, compares the number of vertices, compares with the completeness condition
 *
 * Time complexity: O(|V|)
 * @return bool graph is complete
 */
bool graph_is_complete() {
	timer_start();

	// max edges for one node -> node_count - 1

	unsigned int node_count = graph_get_node_count();
	unsigned int max_node_edge_count = node_count - 1;

	for (unsigned int i = 1; i <= node_count; i++) {
		if (node_get_edge_count(graph_get_node_by_index(i)) != max_node_edge_count) {
			timer_stop();
			return false;
		}
	}

	timer_stop();
	return true;
}

/**
 * @brief Loops through all nodes, compares each vertex count, compares and selects the largest vertex
 *
 * Time complexity: O(|V|)
 * @return unsigned int return the maximum degree (or valence) of the vertex of the graph
 */
unsigned int graph_get_max_degree() {
	timer_start();

	unsigned int max = 0;
	unsigned int node_count = graph_get_node_count();

	for (unsigned int i = 1; i <= node_count; i++) {
		unsigned int edge_count = node_get_edge_count(graph_get_node_by_index(i));

		if (max < edge_count) {
			max = edge_count;
		}
	}

	timer_stop();

	return max;
}

/**
 * @brief Get node count function with timer
 *
 * Time complexity: O(1)
 * @return unsigned int
 */
unsigned int graph_get_node_count_wt() {
	timer_start();

	unsigned int result = graph_get_node_count();

	timer_stop();

	return result;
}

/**
 * @brief Get edges count of graph with deep search
 *
 * Time complexity: O(|V|+|E|)
 * @return unsigned int total edge count
 */
unsigned int graph_get_edge_count() {
	timer_start();

	unsigned int node_count = graph_get_node_count();
	unsigned int edges_count = 0;

	for (unsigned int i = 1; i <= node_count; ++i) {
		edges_count += node_get_edge_count(graph_get_node_by_index(i));
	}

    timer_stop();
    return edges_count / 2;
}

/**
 * @brief Get cycle count of graph with deep search
 *
 * Time complexity: O(|V|+|E|)
 * @return unsigned int total cycle count
 */
unsigned int graph_get_cycle_count() {
	timer_start();

	unsigned int node_count = graph_get_node_count();

	bool* visited = mem_alloc(node_count, sizeof(bool));

	memset(visited, 0, node_count * sizeof(bool));

	unsigned int* path = mem_alloc(node_count, sizeof(unsigned int));

	unsigned int** unique_cycles = mem_alloc(node_count * 1000, sizeof(unsigned int*));

	for (unsigned int i = 0; i < node_count; i++) {
	    unique_cycles[i] = mem_alloc(node_count * 1000, sizeof(unsigned int));
	}

	unsigned int cycle_count = 0;

	for (unsigned int i = 0; i < node_count; i++) {
    depth_first_search_cycle(visited, path, 0, i + 1, i + 1, &cycle_count, node_count, unique_cycles);
	}
	
	free(*unique_cycles);

	free(visited);
	free(path);

	timer_stop();

	return cycle_count;
}

/**
 * @brief Graph is a tree if it has no cycles and is connected
 *
 * Time complexity: O(|V|+|E|)
 * @return bool graph is tree
 */
bool graph_is_tree() {
	timer_start();

	bool result = graph_get_cycle_count() == 0 && graph_is_connected();

	timer_stop();

	return result;
}

/**
 * @brief Graph is forest if it has no cycles and is not connected
 *
 * Time complexity: O(|V|+|E|)
 * @return bool graph is forest
 */
bool graph_is_forest() {
	timer_start();

	bool result = graph_get_cycle_count() == 0 && !graph_is_connected();

	timer_stop();

	return result;
}

/**
 * @brief analyze graph properties and print them
 */
void graph_analyze_properties() {
	printf("===========================================================\n");
	printf("Node count:        \t %d", graph_get_node_count_wt());
	timer_print();
	printf("Edge count:        \t %d", graph_get_edge_count());
	timer_print();
	printf("Cycle count:       \t %d", graph_get_cycle_count());
	timer_print();
	printf("Maximum degree:    \t %d", graph_get_max_degree());
	timer_print();
	printf("Graph is connected:\t %s", graph_is_connected() ? "yes" : "no");
	timer_print();
	printf("Graph is complete: \t %s", graph_is_complete() ? "yes" : "no");
	timer_print();
	printf("Graph is tree:     \t %s", graph_is_tree() ? "yes" : "no");
	timer_print();
	printf("Graph is forest    \t %s", graph_is_forest() ? "yes" : "no");
	timer_print();
	printf("===========================================================\n");
}
