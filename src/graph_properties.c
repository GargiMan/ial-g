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
#include "../include/graph_properties.h"
#include "../include/graph.h"

/**
 * @brief loops through all nodes, compares each vertex count, compares and selects the largest vertex.
 * @warning if an error occurs, -1 is returned
 * @return int Return the maximum degree (or valence) of the vertex of the graph
 */
int graph_max_numb_degree()
{
	int max = -1;
	int node_count = graph_get_node_count();
	for (int i = 0; i < node_count; i++)
	{
		int numb = graph_get_edge_count();
		if (numb > max)
		{
			max = numb;
		}
	}
	return max;
}

void graph_analyze_properties()
{
	printf("Node count: %d\n", graph_get_node_count());
	printf("Edge count: %d\n", graph_get_edge_count());

	printf("Maximum degree: %d\n", graph_max_numb_degree());
	// call property functions
}
