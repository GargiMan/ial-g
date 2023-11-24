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
		return NULL;
    }
    return ptr;
}

void* mem_realloc(void* prevPtr, size_t size) 
{
    void* ptr = realloc(prevPtr, size);
    if (!ptr) {
        return NULL;
    }
    return ptr;
}

void array_free(bool **items)
{
    free(*items);
    *items = NULL;
}

void mem_free(void* ptr) 
{
    free(ptr);
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
void search_all_cycles(node_t *node, unsigned int start_node_index, bool *visited, unsigned int visited_count, bool **cycles, unsigned int *cycles_count, unsigned int node_count)
{
	unsigned int node_index = node_get_index(node);

    if (visited[node_index]) {
        if (node_index == start_node_index && visited_count >= 3) {
            for (unsigned int i = 0; i < *cycles_count; i++) {
                bool is_same_cycle = true;
                for (unsigned int j = 0; j < node_count; j++) {
                    if (cycles[i][j] != visited[j]) {
                        is_same_cycle = false;
                        break;
                    }
                }
                if (is_same_cycle) {
                    return; 
                }
            }

            cycles[*cycles_count] = malloc(node_count * sizeof(bool));
            for (unsigned int i = 0; i < node_count; i++) {
                cycles[*cycles_count][i] = visited[i];
            }
            (*cycles_count)++;
        }
        return;
    }

    visited[node_index] = true;
    visited_count++;

    for (unsigned int i = 0; i < node_get_edge_count(node); i++) {
        search_all_cycles(node_get_edge_node_by_index(node, i), start_node_index, visited, visited_count, cycles, cycles_count, node_count);
    }

    visited[node_index] = false;
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

    unsigned int node_count = graph_get_node_count();
    bool *visited = mem_alloc(node_count, sizeof(bool));

    for (unsigned int i = 0; i < node_count; i++)
    {
        visited[i] = false;
    }

    depth_first_search(graph_get_node_by_index(0), visited);

    for (unsigned int i = 0; i < node_count; i++)
    {
        if (!visited[i])
        {
            timer_stop();
            array_free(&visited);
            return false;
        }
    }

    timer_stop();
    array_free(&visited);

    return true;
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

	unsigned int node_count = graph_get_node_count();
	unsigned int edges_count = 0;

	bool *edges = (bool *)mem_alloc(node_count * node_count, sizeof(bool));
	if (edges == NULL) 
		return 0;
	

	for (unsigned int i = 0; i < node_count * node_count; ++i) 
		edges[i] = false;

	for (unsigned int i = 0; i < node_count; ++i) 
	{
		node_t *node = graph_get_node_by_index(i);
		unsigned int node_edge_count = node_get_edge_count(node);

		for (unsigned int j = 0; j < node_edge_count; ++j) 
		{
        		node_t *neighbour = node_get_edge_node_by_index(node, j);
			unsigned int neighbour_index = node_get_index(neighbour);
			unsigned int edge_index = i * node_count + neighbour_index;
            
        		if (!edges[edge_index]) 
			{
        		edges[edge_index] = true;
        		edges_count++;
        		}
		}
	}

    	mem_free(edges);

    	timer_stop();
    	return edges_count / 2;
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
		return 0;
	

    	bool *visited = mem_alloc(node_count, sizeof(bool));
    	bool **cycles = mem_alloc(max_cycles_count, sizeof(bool *));

    	for (unsigned int i = 0; i < max_cycles_count; i++) 
        	cycles[i] = NULL;
    
    	unsigned int cycles_count = 0;
	
    	for (unsigned int i = 0; i < node_count; i++) 
        	search_all_cycles(graph_get_node_by_index(i), i, visited, 0, cycles, &cycles_count, node_count);
    

    	for (unsigned int i = 0; i < cycles_count; i++) 
        	free(cycles[i]);
    
    	mem_free(cycles);
    	mem_free(visited);

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
