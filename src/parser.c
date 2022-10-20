/**
 * @file parser.c
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#include "../include/parser.h"
#include "../include/graph.h"
#include "../include/error.h"
#include <stdbool.h>
#include <string.h>

void parse_data(FILE* stream) {
    
    graph_init();
    
    char node_name[256];
    char node2_name[256];
    bool done_nodes = false;
    bool done_edges = false;
    
    int lines = 1;
    for (int columns = 1; !done_edges || !done_nodes; columns++) {
        
        char last_char = fgetc(stream);
        
        if ((lines == 1 || lines == 2) && columns == 1) {
            if (last_char != '{') {
                error_exit(graphSyntaxError, "Graph %s list must start with '{' at position %i:%i\n", lines == 1 ? "node" : "edge" , lines, columns);
            } else {
                continue;
            }
        }

        switch (last_char) {
            
            case '}':
                if (lines == 1 && columns > 1 && !done_nodes && !done_edges) {
                    done_nodes = true;
                    if (graph_get_node_count() == 0) {
                        error_exit(graphNodeCountZeroError, "Graph must have at least one node\n");
                    }
                } else if (done_nodes && !done_edges) {
                    done_edges = true;
                } else {
                    error_exit(graphSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
                }
                break;

            case '\n':
                if (!done_nodes) {
                    error_exit(graphSyntaxError, "Graph nodes are not finished, unexpected 'EOL' on first line\n");
                }
                lines++;
                columns = 0;
                break;

            case -1:
                if (!done_nodes || !done_edges) {
                    error_exit(graphSyntaxError, "Graph is not finished, unexpected 'EOF'\n");
                }
                return;
            
            case ',':
                if (strlen(node_name) == 0) {
                    error_exit(graphSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
                }
                break;
            
            default:
                if (!((last_char >= 'a' && last_char <= 'z') || (last_char >= 'A' && last_char <= 'Z') || (last_char >= '0' && last_char <= '9'))) {
                    error_exit(graphSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
                }

                node_name[strlen(node_name)] = last_char;
                break;
        
        }
    
        if ((last_char == ',' || last_char == '}') && strlen(node_name) != 0) {
            graph_create_node(node_name);
            for (int i = 0; i < (int)strlen(node_name); i++) {
                node_name[i] = '\0'; 
            }
        }
    }
}
