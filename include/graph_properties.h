/**
 * @file graph_properties.h
 * @authors Marek Gergel (xgerge01), Jindřich Šíma (xsimaj04) + Others(replace)
 * @brief declaration of functions for graph analysis and their subsequent execution
 * @version 0.1
 * @date 2022-10-26
 * @todo add names of others members
 * @copyright Copyright (c) 2022
 *
 */

#ifndef GRAPH_PROPERTIES_H
#define GRAPH_PROPERTIES_H
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void graph_analyze_properties();
    extern bool graph_is_connected_graph();
    extern bool graph_is_complete_graph();
    extern bool graph_is_isolated();
    extern int graph_max_numb_degree();

#ifdef __cplusplus
}
#endif

#endif // GRAPH_PROPERTIES_H
