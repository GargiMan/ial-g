/**
 * @file graph_properties.c
 * @authors Marek Gergel (xgerge01), Jindřich Šíma (xsimaj04), Tomáš Fišer (xfiser16), Dmytro Sadovskyi (xsadov06)
 * @brief definition of functions and variables for graph analysis and their subsequent execution,
 * time complexity description (|V| = number of vertices (nodes), |E| = number of edges)
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
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
    visited[node_index] = true;

    // Explore all unvisited neighbors
    for (unsigned int i = 0; i < node_get_edge_count(node); i++)
    {
        node_t *neighbor = node_get_edge_node_by_index(node, i);
        unsigned int neighbor_index = node_get_index(neighbor);

        if (!visited[neighbor_index])
        {
            depth_first_search(neighbor, visited);
        }
    }
}

/**
 * @brief Get all cycles in graph with depth first search
 * @param visited visited nodes bit array
 * @param cycle_len_remaining cycle length remaining to search
 * @param node_index current node index
 * @param cycle_start_node_index cycle start node index
 * @param cycle_count pointer to count of all cycles of specific length
 */
void depth_first_search_cycle(bool* visited, unsigned int cycle_len_remaining, unsigned int node_index, unsigned int cycle_start_node_index, unsigned int* cycle_count) {
	visited[node_index - 1] = true;
	node_t *node = graph_get_node_by_index(node_index);

	if (cycle_len_remaining == 0) {
		visited[node_index - 1] = false;

		// check if node is connected to cycle start node
		for (unsigned int i = 0; i < node_get_edge_count(node); i++) {
			if (node_get_index(node_get_edge_node_by_index(node, i)) == cycle_start_node_index) {
				(*cycle_count)++;
				return;
			}
		}
		return;
	}

	// search for next node
	for (unsigned int i = 0; i < node_get_edge_count(node); i++) {
		node_t *edge_node = node_get_edge_node_by_index(node, i);
		unsigned int edge_node_index = node_get_index(edge_node);

		if (!visited[edge_node_index - 1]) {
			depth_first_search_cycle(visited, cycle_len_remaining - 1, edge_node_index, cycle_start_node_index, cycle_count);
		}
	}

	// reset node visit for next cycle
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

	double node_count = graph_get_node_count();

    unsigned int cycles_count = 0;

	for (unsigned int cycle_len = 3; cycle_len <= node_count; cycle_len++) {

		bool *visited = mem_alloc(node_count, sizeof(bool));
		memset(visited, 0, node_count * sizeof(bool));

		unsigned int cycles_count_for_len = 0;
		for (unsigned int i = 1; i <= (node_count - (cycle_len - 1)); i++) {
			depth_first_search_cycle(visited, cycle_len - 1, i, i, &cycles_count_for_len);
			visited[i - 1] = true;
		}
		//cycles_count_for_len is doubled because of undirected graph
		cycles_count += cycles_count_for_len / 2;

		free(visited);
	}

	timer_stop();

	return cycles_count;
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
