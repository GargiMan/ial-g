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

int lines = 1;
int columns = 1;
int line_digit_count = 0;
int column_digit_count = 0;

/**
 * @brief Function parse edge data to graph structure
 */
void parse_edge_data()
{    
    char last_char = fgetc(stream_s);

    while (last_char != EOF)
    {
        //Counting number of digits 
        line_digit_count = 0;
        int temp_lines = lines;
        if (temp_lines != 0)
        {
            while(temp_lines != 0)  
            {  
                temp_lines = temp_lines/10;  
                line_digit_count++;  
            } 
        }
        else 
        {
            line_digit_count = 1;
        }
        
        //Creating name from line number
        char node_name[line_digit_count + 1];
        sprintf(node_name, "%d", lines);
        graph_create_node(node_name);

        for (int column_index = 1; column_index <= lines; column_index++)
        {
            while (last_char == ' ')
            {
                last_char = fgetc(stream_s);
            }

            if (!(last_char == '0' || last_char == '1'))
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, column_index);
            }

            if (last_char == '1')
            {
                column_digit_count = 0;
                int temp_column = column_index;
                if (temp_column != 0)
                {
                    while(temp_column != 0)  
                    {  
                        temp_column = temp_column/10;  
                        column_digit_count++;  
                    }
                }
                else 
                {
                    column_digit_count = 1;
                }
                // Creating name from column index
                char node_name2[column_digit_count + 1];
                sprintf(node_name2, "%d", column_index);
                graph_create_edge(node_name, node_name2);
            }

            last_char = fgetc(stream_s);
        }

        last_char = fgetc(stream_s);
        lines++;
    }
}

/**
 * @brief Function reads data from stream and parse them to graph sctructure
 * @param stream data input stream
 */
void parse_data(FILE *stream)
{
    graph_init();

    stream_s = stream;

    parse_edge_data();
}
