#include "graph.h"

int main(){
    FILE *file = fopen("test", "r");
    if (file == NULL){
        printf("File could not be opened\n");
        return 1;
    }

    int node_cnt = 0;
    int edge_cnt = 0;
    char i;
    while ((i = fgetc(file)) != '\n'){
        if(i == EOF)
            break;
        if((i == '0') || (i == '1')){
            node_cnt++;
        }
    }

    fseek(file, 0, SEEK_SET);

    while ((i = fgetc(file)) != EOF){
        if((i == '0') || (i == '1'))
            edge_cnt++;
    }

    if(node_cnt*node_cnt != edge_cnt){
        printf("Invalid matrix format\n");
        return 1;
    }

    printf("number of nodes: %d\n", node_cnt);
    printf("number of edges: %d\n", edge_cnt);
    fclose(file);
}