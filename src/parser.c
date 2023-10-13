/**
 * @file parser.c
 * @author Marek Gergel (xgerge01)
 * @brief definition of functions and variables for parsing input with graph data
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/parser.h"

FILE *stream_s;

// Node indexes
int lines = 1;
int columns = 1;

// Last char from stream
char last_char;

/**
 * @brief Get the char from saved stream
 * @return char from stream
 */
char get_char() 
{
    return (last_char = fgetc(stream_s));
}

/**
 * @brief Function reads graph data from stream and parse them to graph sctructure
 * @param stream data input stream
 */
void parse_data(FILE *stream)
{
    graph_init();

    stream_s = stream;

    while (get_char() != EOF)
    {
        //Creating name from line number, indexing from 1
        char node_name[32];
        sprintf(node_name, "%d", lines);

        graph_create_node(node_name);

        for (columns = 1; columns < lines; columns++)
        {
            // Skips spaces
            while (last_char == ' ') get_char();

            if (columns == lines && last_char != '0') {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }

            // Creating name from column index, indexing from 1
            char node_name2[32];
            sprintf(node_name2, "%d", columns);

            switch (last_char)
            {
                case ' ':
                    columns--;
                    break;
                case '0':
                    break;
                case '1':
                    graph_create_edge(node_name, node_name2);
                    break;
                case EOF:
                    error_exit(parserSyntaxError, "Graph is not finished, unexpected 'EOF'\n");
                    break;
                default:
                    error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
                    break;
            }
        }

        // Skips characters above main diagonal
        while (get_char() != '\n' && last_char != EOF);
        
        lines++;
    }

    if (lines == 1 && last_char == EOF)
    {
        error_exit(parserSyntaxError, "Graph is empty\n");
    }
}
