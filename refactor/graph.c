#include "graph.h"

bool** graph_init(int node_cnt) {
    bool **graph = (bool **)calloc(node_cnt, sizeof(bool *));
    if (graph == NULL) {
        return 1;
    }

      for (int i = 0; i < node_cnt; i++) {
        graph[i] = (bool *)calloc(node_cnt, sizeof(bool));
        if (graph[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(graph[j]);
            
            free(graph);
            
            return 1;
        }
    }
    return **graph;
}

void graph_set(int x, int y, bool value, bool **graph){
    graph[x][y] = value;
}

void graph_print(bool **graph, int node_cnt){
    for(int i = 0; i < node_cnt; i++){
        for(int j = 0; j < node_cnt; j++){
            printf("%d, ", graph[i][j]);
        }
    }
}

void graph_destroy(bool **graph, int node_cnt){
    for(int i = 0; i < node_cnt; i++){
        for(int j = 0; j < node_cnt; j++){
            printf("%d, ", graph[i][j]);
        }
    }
}

