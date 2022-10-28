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
#include "../include/DLList.h"
#include <time.h>

bool graph_is_complete_graph()
{
}

/**
 * @brief Loops through all nodes, compares each vertex count, compares and find an isolated vertex.
 * @author Jindřich Šíma (xsimaj04)
 * @warning If an error occurs, -1 is returned.
 * @return true if there is at least one isolated node.
 * @return false if there are no isolated nodes.
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
 * @warning If an error occurs, -1 is returned.
 * @return int Return the maximum degree (or valence) of the vertex of the graph.
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

bool graph_is_forest()
{
    DLList path, visited;
	bool back=false;
	struct node *current, *tmp;
	int node_count = graph_get_node_count();
    DLL_Init(&path);
	DLL_Init(&visited);
	current=graph->nodes[0];
	tmp = NULL;
	DLL_InsertLast(&path, current);
	DLL_InsertLast(&visited, current);
	DLL_Last(&path);
	DLL_VisitedInc(&path);
	for(;;)
	{
		if (current->edge_count < 1 || DLL_Visited(&path) == current->edge_count)
		{
			if (!DLL_IsOne(&path))
			{
				DLL_DeleteLast(&path);
				DLL_Last(&path);
				DLL_GetLast(&path, &current);
				back = true;
				continue;
			}
			if ((current->edge_count == DLL_Visited(&path))&& DLL_IsOne(&path))
			{
				if (DLL_Len(&visited) == node_count) return true;
				else
				{
					for (int i = 0; i < node_count; i++)
					{
						if (!DLL_IsIn(&visited, graph->nodes[i]))
						{
							DLL_Dispose(&path);
							DLL_Init(&path);
							current = graph->nodes[i];
							DLL_InsertLast(&path, current);
							DLL_InsertLast(&visited, current);
							DLL_Last(&path);
							back = false;
							DLL_GetLast(&path, &current);
							DLL_VisitedInc(&path);
							break;
						}
					}
				}
				continue;
			}
		}
		else
		{
			DLL_Previous(&path);
		 	DLL_GetValue(&path, &tmp);
			DLL_Last(&path);
			current=current->edge_nodes[DLL_Visited(&path)];
			if (tmp != NULL)
			{
				if (!strcmp(current->name, tmp->name)) //?
				{
					DLL_GetLast(&path, &current);
					DLL_VisitedInc(&path);
					continue;
				}
			}
			DLL_VisitedInc(&path);
			DLL_InsertLast(&path, current);
			DLL_Last(&path);
			DLL_VisitedInc(&path);
		 	if (DLL_IsIn(&visited, current) && back == false)
		 	{
		 		return false;
		 	}
		 	DLL_InsertLast(&visited, current);
			back=false;

		}
	}
}

bool graph_is_tree(bool forest, bool continuous)
{
	return forest && continuous;
}

/**
 * @brief analyze properties of a graph
 *
 */
void graph_analyze_properties()
{
	printf("Node count: %d\n", graph_get_node_count());
	printf("Edge count: %d\n", graph_get_edge_count());
	printf("Maximum degree: %d\n", graph_max_numb_degree());
	printf("Graph is an isolated: %s\n", graph_is_isolated() == true ? "yes" : "no");
	time_t t0 = time(0);
	for (int i = 0; i < 1000000; i++)
	{
		graph_is_forest();
	}
	time_t t1 = time(0);
	double time_in_seconds = difftime(t1, t0);
	printf("Seconds: %f\n", time_in_seconds);
	printf("Graph is an forest: %s\n", graph_is_forest() == true ? "yes" : "no");
	//printf("Graph is an tree: %s\n", graph_is_tree(forest, continuous) == true ? "yes" : "no");
	getch();
}
