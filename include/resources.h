/**
 * @file resources.h
 * @author Marek Gergel (xgerge01)
 * @brief
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RESOURCES_H
#define RESOURCES_H

#include "graph.h"

#define FREE_RESOURCES   \
    do {                 \
        graph_destroy(); \
    } while (0)

#endif // RESOURCES_H
