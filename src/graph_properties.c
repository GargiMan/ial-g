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

/**
 * @brief Check if items array contains item, if not, add it.
 * @param item new item to check and add
 * @param items pointer to array with all items
 * @param items_count pointer to items count in array
 */
void array_add_item(uint64_t item, uint64_t *items, unsigned int *items_count)
{
	// xor item with all items to detect if item is already in items array
	for (unsigned int i = 0; i < *items_count; i++)
	{
		// item is already in items
		if ((item ^ items[i]) == 0)
		{
			return;
		}
	}

	// item not found in items, add it
	// item count has to be retyped to uint64_t to right memory access
	items[(uint64_t)*items_count] = item;
	(*items_count)++;
}

/**
 * @brief deep first search function
 *  It goes through all neighbors of the inserted nodes,
 *  if any of them has already been checked, it skips,
 *  otherwise the selected one is called recursively until all nodes are checked.
 * @param node node to be searched
 * @param visited bit array of visited nodes
 */
void deep_first_search(node_t *node, uint64_t *visited)
{
	uint64_t current_node_bit = (uint64_t)1 << node_get_index(node);

	// if node is already visited, return visited nodes
	if (current_node_bit & *visited)
	{
		return;
	}

	// mark node as visited
	*visited |= current_node_bit;

	unsigned int node_edge_count = node_get_edge_count(node);

	// go through all neighbors
	for (unsigned int i = 0; i < node_edge_count; i++)
	{
		deep_first_search(node_get_edge_node_by_index(node, i), visited);
	}
}

/**
 * @brief Get factorial of a number
 * @param n number to get factorial of
 * @return unsigned int result of factorial
 */
unsigned int fact(int n)
{
	if (n < 2)
	{
		return 1;
	}

	return n * fact(n - 1);
}

/**
 * @brief Get the max cycle count
 * @param n node count
 * @param r max size of cycle
 * @return unsigned int max cycle count
 */
unsigned int get_max_cycle_count(int n, int r)
{
	// minimal cycle size is 3
	if (r < 3 || n < 3)
	{
		return 0;
	}

	// cycle count (r nodes in cycle of n nodes)  n!/((n-r)!*r!)
	// recursive (cycle count for r size) + (cycle count for r-1 size) + ...
	return (fact(n) / (fact(n - r) * fact(r))) + get_max_cycle_count(n, r - 1);
}

/**
 * @brief Get all cycles in graph with deep search
 * @param node node to be searched
 * @param start_node_index index of start node
 * @param visited visited nodes bit array
 * @param visited_count count of visited nodes
 * @param cycles pointer to bit array with all cycles
 * @param cycles_count pointer to count of all cycles in array
 */
void search_all_cycles(node_t *node, unsigned int start_node_index, uint64_t visited, unsigned int visited_count, uint64_t *cycles, unsigned int *cycles_count)
{
	uint64_t current_node_bit = (uint64_t)1 << graph_get_node_index(node);

	// if node is already visited, return visited nodes
	if (current_node_bit & visited)
	{
		uint64_t start_node_bit = (uint64_t)1 << start_node_index;

		// cycle must be of at least 3 nodes
		if ((current_node_bit & start_node_bit) && (visited_count > 2))
		{
			array_add_item(visited, cycles, cycles_count);
		}
		return;
	}

	// increment nodes visited
	visited_count++;
	// mark node as visited
	visited |= current_node_bit;

	unsigned int node_edge_count = node_get_edge_count(node);

	// go through all neighbors
	for (unsigned int i = 0; i < node_edge_count; i++)
	{
		search_all_cycles(node_get_edge_node_by_index(node, i), start_node_index, visited, visited_count, cycles, cycles_count);
	}
}

/**
 * @brief Get all edges in graph
 * @param node node to be searched
 * @param edges pointer to bit array with all edges
 * @param edges_count pointer to count of all edges in array
 */
void search_all_edges(node_t *node, uint64_t *edges, unsigned int *edges_count)
{
	uint64_t current_node_bit = (uint64_t)1 << graph_get_node_index(node);

	unsigned int node_edge_count = node_get_edge_count(node);

	// go through all neighbors
	for (unsigned int i = 0; i < node_edge_count; i++)
	{
		uint64_t neighbor_node_bit = (uint64_t)1 << graph_get_node_index(node_get_edge_node_by_index(node, i));
		array_add_item((current_node_bit | neighbor_node_bit), edges, edges_count);
	}
}

/**
 * @brief deep-first search function to determine if the graph is continuous.
 *
 * Time complexity: O(|V|+|E|)
 * @return bool graph is connected
 */
bool graph_is_connected()
{
	timer_start();

	// use deep first search from first node
	uint64_t visited = 0;

	deep_first_search(graph_get_node_by_index(0), &visited);

	uint64_t all_visited = (1 << graph_get_node_count()) - 1;

	bool result = (visited == all_visited);

	timer_stop();

	return result;
}

/**
 * @brief Loops through all nodes, compares the number of vertices, compares with the completeness condition.
 *
 * Time complexity: O(|V|)
 * @return bool graph is complete
 */
bool graph_is_complete()
{
	timer_start();

	// max edges for one node -> node_count - 1

	unsigned int node_count = graph_get_node_count();
	unsigned int max_node_edge_count = node_count - 1;

	for (unsigned int i = 0; i < node_count; i++)
	{
		if (node_get_edge_count(graph_get_node_by_index(i)) != max_node_edge_count)
		{
			timer_stop();
			return false;
		}
	}

	timer_stop();
	return true;
}

/**
 * @brief Loops through all nodes, compares each vertex count, compares and selects the largest vertex.
 *
 * Time complexity: O(|V|)
 * @return unsigned int return the maximum degree (or valence) of the vertex of the graph
 */
unsigned int graph_get_max_degree()
{
	timer_start();

	unsigned int max = 0;
	unsigned int node_count = graph_get_node_count();

	for (unsigned int i = 0; i < node_count; i++)
	{
		unsigned int edge_count = node_get_edge_count(graph_get_node_by_index(i));

		if (max < edge_count)
		{
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
unsigned int graph_get_node_count_wt()
{
	timer_start();

	unsigned int result = graph_get_node_count();

	timer_stop();

	return result;
}

/**
 * @brief Get edges count of graph with deep search.
 *
 * Time complexity: O(|V|+|E|)
 * @return unsigned int total edge count
 */
unsigned int graph_get_edge_count()
{
	timer_start();

	// max total edges for all nodes -> node_count * (node_count - 1) / 2

	unsigned int node_count = graph_get_node_count();
	unsigned int max_edges_count = node_count * (node_count - 1) / 2;

	if (max_edges_count == 0)
	{
		return 0;
	}

	// array of edges, one edge is bit array of visited nodes
	// 0 - not in edge, 1 - in edge
	uint64_t edges[max_edges_count];
	for (unsigned int i = 0; i < max_edges_count; i++)
	{
		edges[i] = 0;
	}

	unsigned int edges_count = 0;

	for (unsigned int i = 0; (i < node_count) && (edges_count != max_edges_count); i++)
	{
		search_all_edges(graph_get_node_by_index(i), edges, &edges_count);
	}

	timer_stop();

	return edges_count;
}

/**
 * @brief Get cycle count of graph with deep search.
 *
 * Time complexity: O(|V|+|E|)
 * @return unsigned int total cycle count
 */
unsigned int graph_get_cycle_count()
{
	timer_start();

	unsigned int node_count = graph_get_node_count();
	unsigned int max_cycles_count = get_max_cycle_count(node_count, node_count);

	if (max_cycles_count == 0)
	{
		return 0;
	}

	// array of cycles, one cycle is bit array of visited nodes
	// 0 - not in cycle, 1 - in cycle
	uint64_t cycles[max_cycles_count];
	for (unsigned int i = 0; i < max_cycles_count; i++)
	{
		cycles[i] = 0;
	}

	unsigned int cycles_count = 0;

	for (unsigned int i = 0; (i < node_count) && (cycles_count != max_cycles_count); i++)
	{
		search_all_cycles(graph_get_node_by_index(i), i, 0, 0, cycles, &cycles_count);
	}

	timer_stop();

	return cycles_count;
}

/**
 * @brief Graph is a tree if it has no cycles and is connected.
 *
 * Time complexity: O(|V|+|E|)
 * @return bool graph is tree
 */
bool graph_is_tree()
{
	timer_start();

	bool result = graph_get_cycle_count() == 0 && graph_is_connected();

	timer_stop();

	return result;
}

/**
 * @brief Graph is forest if it has no cycles and is not connected.
 *
 * Time complexity: O(|V|+|E|)
 * @return bool graph is forest
 */
bool graph_is_forest()
{
	timer_start();

	bool result = graph_get_cycle_count() == 0 && !graph_is_connected();

	timer_stop();

	return result;
}

/**
 * @brief analyze graph properties and print them
 */
void graph_analyze_properties()
{

	printf("===========================================================\n");
	printf("Node count:\t\t %d", graph_get_node_count_wt());
	timer_print();
	printf("Edge count:\t\t %d", graph_get_edge_count());
	timer_print();
	printf("Cycle count:\t\t %d", graph_get_cycle_count());
	timer_print();
	printf("Maximum degree:\t\t %d", graph_get_max_degree());
	timer_print();
	printf("Graph is connected:\t %s", graph_is_connected() ? "yes" : "no");
	timer_print();
	printf("Graph is complete:\t %s", graph_is_complete() ? "yes" : "no");
	timer_print();
	printf("Graph is tree:\t\t %s", graph_is_tree() ? "yes" : "no");
	timer_print();
	printf("Graph is forest\t\t %s", graph_is_forest() ? "yes" : "no");
	timer_print();
	printf("===========================================================\n");
}
