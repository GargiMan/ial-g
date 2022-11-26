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

    extern bool graph_is_connected();
    extern bool graph_is_complete();
    extern bool graph_is_tree();
    extern bool graph_is_forest();
    extern bool graph_has_isolated_node();
    extern unsigned int graph_get_max_degree();
    extern unsigned int graph_get_cycle_count();
    void graph_analyze_properties();

#ifdef __cplusplus
}
#endif

#endif // GRAPH_PROPERTIES_H
