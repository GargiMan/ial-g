/**
 * @file graph_properties.c
 * @authors Marek Gergel (xgerge01), Jindřich Šíma (xsimaj04) + Others(replace)
 * @brief definition of functions for graph analysis and their subsequent execution
 * @version 0.1
 * @date 2022-10-26
 * @todo add names of others members
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "../include/graph_properties.h"
#include "../include/graph.h"

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
		if (graph->nodes[i] == node)
		{
			return i;
		}
	}
	return 0;
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
	uint64_t current_node_bit = (uint64_t)1 << graph_get_node_index(node);

	// if node is already visited, return visited nodes
	if (current_node_bit & *visited)
	{
		return;
	}

	// mark node as visited
	*visited |= current_node_bit;

	// go through all neighbors
	for (unsigned int i = 0; i < node->edge_count; i++)
	{
		deep_first_search(node->edge_nodes[i], visited);
	}
}

/**
 * @brief Get factorial of a number
 * @param n number to get factorial of
 * @return int result of factorial
 */
unsigned int fact(int n)
{
	if (n <= 1)
	{
		return 1;
	}

	return n * fact(n - 1);
}

/**
 * @brief Get the max cycle count
 * @param n node count
 * @param r max size of cycle
 * @return int max cycle count
 */
unsigned int get_max_cycle_count(int n, int r)
{
	if (r < 3 || n < 3)
	{
		return 0;
	}

	// cycle count (r size of n nodes)  n!/((n-r)!*r!)
	return fact(n) / (fact(n - r) * fact(r)) + get_max_cycle_count(n, r - 1);
}

/**
 * @brief Check if cycles array contains cycle, if not, add it
 * @param cycle new cycle to check
 * @param cycles pointer to array with all cycles
 * @param cycles_count pointer to cycles count in array
 */
void cycle_add(uint64_t cycle, uint64_t *cycles, unsigned int *cycles_count)
{
	// xor cycle with all cycles to detect if cycle is already in cycles array
	for (unsigned int i = 0; i < *cycles_count; i++)
	{
		// cycle is already in cycles
		if ((cycle ^ cycles[i]) == 0)
		{
			return;
		}
	}

	// cycle not found in cycles, add it
	// cycle count has to be retyped to uint64_t to right memory access
	cycles[(uint64_t)*cycles_count] = cycle;
	(*cycles_count)++;
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
void deep_first_search_all_cycles(node_t *node, unsigned int start_node_index, uint64_t visited, unsigned int visited_count, uint64_t *cycles, unsigned int *cycles_count)
{
	uint64_t current_node_bit = (uint64_t)1 << graph_get_node_index(node);

	// if node is already visited, return visited nodes
	if (current_node_bit & visited)
	{
		uint64_t start_node_bit = 1 << start_node_index;

		// cycle must be of at least 3 nodes
		if ((current_node_bit & start_node_bit) && (visited_count > 2))
		{
			cycle_add(visited, cycles, cycles_count);
		}
		return;
	}

	// increment nodes visited
	visited_count++;
	// mark node as visited
	visited |= current_node_bit;

	// go through all neighbors
	for (unsigned int i = 0; i < node->edge_count; i++)
	{
		deep_first_search_all_cycles(node->edge_nodes[i], start_node_index, visited, visited_count, cycles, cycles_count);
	}
}

/**
 * @brief deep-first search function to determine if the graph is continuous.
 * @author Jindřich Šíma (xsimaj04)
 * @return true graph is connected
 */
bool graph_is_connected()
{
	if (graph_has_isolated_node())
	{
		return false;
	}

	// use deep first search from first node
	uint64_t visited = 0;

	deep_first_search(graph->nodes[0], &visited);

	uint64_t all_visited = (1 << graph_get_node_count()) - 1;

	return visited == all_visited;
}

/**
 * @brief Loops through all nodes, compares the number of vertices, compares with the completeness condition.
 * @author Jindřich Šíma (xsimaj04)
 * @return true graph is complete
 */
bool graph_is_complete()
{
	unsigned int node_count = graph_get_node_count();

	// max edges for one node -> node_count - 1
	// max edges for all nodes -> node_count * (node_count - 1)
	// max total edges for all nodes -> node_count * (node_count - 1) / 2

	unsigned int max_node_edge_count = node_count - 1;

	for (unsigned int i = 0; i < node_count; i++)
	{
		if (graph->nodes[i]->edge_count != max_node_edge_count)
		{
			return false;
		}
	}

	return true;
}

/**
 * @brief Loops through all nodes, compares each vertex count, compares and find an isolated vertex.
 * @author Jindřich Šíma (xsimaj04)
 * @return true if there is at least one isolated node
 */
bool graph_has_isolated_node()
{
	unsigned int node_count = graph_get_node_count();

	for (unsigned int i = 0; i < node_count; i++)
	{
		if (graph->nodes[i]->edge_count == 0)
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief Loops through all nodes, compares each vertex count, compares and selects the largest vertex.
 * @author Jindřich Šíma (xsimaj04)
 * @return int return the maximum degree (or valence) of the vertex of the graph
 */
unsigned int graph_get_max_degree()
{
	unsigned int max = 0;
	unsigned int node_count = graph_get_node_count();

	for (unsigned int i = 0; i < node_count; i++)
	{
		if (max < graph->nodes[i]->edge_count)
		{
			max = graph->nodes[i]->edge_count;
		}
	}
	return max;
}

unsigned int graph_get_cycle_count()
{
	unsigned int node_count = graph_get_node_count();
	unsigned int max_cycles_count = get_max_cycle_count(node_count, node_count);

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
		deep_first_search_all_cycles(graph->nodes[i], i, 0, 0, cycles, &cycles_count);
	}

	return cycles_count;
}

/**
 * @brief Graph is forest if it has no cycles
 * @return true when graph is forest
 */
bool graph_is_forest()
{
	return graph_get_cycle_count() == 0;
}

/**
 * @brief Graph is a tree if it is forest (has no cycles) and is connected
 * @return true when graph is tree
 */
bool graph_is_tree()
{
	return graph_is_forest() && graph_is_connected();
}

/**
 * @brief analyze graph properties and print them
 */
void graph_analyze_properties()
{
	printf("==================================\n");
	printf("Node count:\t\t %d\n", graph_get_node_count());
	printf("Edge count:\t\t %d\n", graph_get_edge_count());
	printf("Cycle count:\t\t %d\n", graph_get_cycle_count());
	printf("Maximum degree:\t\t %d\n", graph_get_max_degree());
	printf("Graph is connected:\t %s\n", graph_is_connected() ? "yes" : "no");
	printf("Graph is complete:\t %s\n", graph_is_complete() ? "yes" : "no");
	printf("Graph is tree:\t\t %s\n", graph_is_tree() ? "yes" : "no");
	printf("Graph is forest\t\t %s\n", graph_is_forest() ? "yes" : "no");
	printf("==================================\n");
}
