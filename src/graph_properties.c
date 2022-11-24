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
 * @brief deep first search function
 *  It goes through all neighbors of the inserted nodes,
 *  if any of them has already been checked, it skips,
 *  otherwise the selected one is called recursively until all nodes are checked.
 * @param n input node for DFS
 */
void DFS(node_t *n)
{
	n->visited = 1;
	int neb = n->edge_count;
	for (int i = 0; i < neb; i++)
	{
		if (n->edge_nodes[i]->visited != 1)
		{
			DFS(n->edge_nodes[i]);
		}
	}
}

/**
 * @brief deep-first search function to determine if the graph is continuous.
 * @author Jindřich Šíma (xsimaj04)
 * @return true graph is connected
 */
bool graph_is_connected_graph()
{
	if (graph_is_isolated()) // if the graph is isolated it may not continue.
	{
		return false;
	}
	int node_count = graph_get_node_count();

	DFS(graph->nodes[0]); // deep-first search

	/**
	 * all nodes are passed through,
	 * if some nodes have not been visited it is a disconnected graph.
	 */
	for (int k = 0; k < node_count; k++)
	{
		if (graph->nodes[k]->visited == 0)
		{
			return false;
		}
	}
	return true;
}

/**
 * @brief Loops through all nodes, compares the number of vertices, compares with the completeness condition.
 * @author Jindřich Šíma (xsimaj04)
 * @return true graph is complete
 */
bool graph_is_complete_graph()
{
	int node_count = graph_get_node_count();
	int mustCount = (node_count * (node_count - 1)) / 2; // The number of edges in the graph must be N(N-1)/2

	for (int k = 0; k < node_count; k++)
	{
		if (graph->nodes[k]->edge_count != mustCount)
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
bool graph_is_isolated()
{
	bool isIsolated = false;
	int node_count = graph_get_node_count();
	for (int i = 0; i < node_count; i++)
	{
		if (graph->nodes[i]->edge_count == 0)
		{
			isIsolated = true;
			break;
		}
	}
	return isIsolated;
}

/**
 * @brief Loops through all nodes, compares each vertex count, compares and selects the largest vertex.
 * @author Jindřich Šíma (xsimaj04)
 * @return int return the maximum degree (or valence) of the vertex of the graph
 */
int graph_max_numb_degree()
{
	int max = -1;
	int node_count = graph_get_node_count();
	for (int i = 0; i < node_count; i++)
	{
		int numb = graph->nodes[i]->edge_count;
		if (numb > max)
		{
			max = numb;
		}
	}
	return max;
}

/**
 * @brief analyze graph properties and print them
 *
 */
void graph_analyze_properties()
{
	printf("================================================\n");
	printf("Node count:            %d\n", graph_get_node_count());
	printf("Edge count:            %d\n", graph_get_edge_count());
	printf("Maximum degree:        %d\n", graph_max_numb_degree());
	if (graph_max_numb_degree() != 0)
	{
		printf("Graph is an isolated:  %s\n", graph_is_isolated() == true ? "yes" : "no");
		printf("Graph is an complete:  %s\n", graph_is_complete_graph() == true ? "yes" : "no");
		printf("Graph is an connected: %s\n", graph_is_connected_graph() == true ? "yes" : "no");
	}
	else
	{
		printf("Graph is an isolated:  EMPTY GRAPH\n");
		printf("Graph is an complete:  EMPTY GRAPH\n");
		printf("Graph is an connected: EMPTY GRAPH\n");
	}
	printf("================================================\n");
}
