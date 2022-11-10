/**
 * @file parser.c
 * @author Marek Gergel (xgerge01)
 * @brief
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

/**
 * @brief Function parse node data to graph structure
 */
void parse_node_data()
{

    bool list_start = false;
    bool list_split = false;
    bool list_end = false;

    char node_name[MAX_NODE_NAME_LENGTH + 1] = "\0";
    ;

    while (!list_end)
    {

        char last_char = fgetc(stream_s);

        switch (last_char)
        {

        case -1:
            error_exit(parserSyntaxError, "Graph is not finished, unexpected 'EOF'\n");
            break;

        case '\n':
        case '\r':
            if (strlen(node_name) != 0)
            {
                error_exit(parserSyntaxError, "Unexpected 'EOL' at position %i:%i\n", lines, columns);
            }
            lines++;
            columns = 0;
            break;

        case '{':
            if (list_start)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            list_start = true;
            break;

        case '}':
            if (!list_start || list_split)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            list_end = true;
            break;

        case ',':
            if (!list_start || strlen(node_name) == 0)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            list_split = true;
            break;

        default:
            if (!list_start || !((last_char >= 'a' && last_char <= 'z') || (last_char >= 'A' && last_char <= 'Z') || (last_char >= '0' && last_char <= '9')))
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }

            list_split = false;

            if (strlen(node_name) == MAX_NODE_NAME_LENGTH)
            {
                error_exit(parserNodeNameLengthOverflowError, "Node name lenght overflow (max %i characters) at position %i:%i\n", MAX_NODE_NAME_LENGTH, lines, columns);
            }
            node_name[strlen(node_name)] = last_char;
            break;
        }

        if ((last_char == ',' || last_char == '}') && strlen(node_name) != 0)
        {
            graph_create_node(node_name);
            for (int i = 0; i < (int)strlen(node_name); i++)
            {
                node_name[i] = '\0';
            }
        }

        columns++;
    }

    if (graph_get_node_count() == 0)
    {
        error_exit(parserNodeCountZeroError, "Graph node list is empty\n");
    }
}

/**
 * @brief Function parse edge data to graph structure
 */
void parse_edge_data()
{

    bool list_start = false;
    bool list_split = true;
    bool list_end = false;

    bool edge_start = false;
    bool edge_split = false;
    bool edge_end = false;

    char node_name[MAX_NODE_NAME_LENGTH + 1] = "\0";
    char node2_name[MAX_NODE_NAME_LENGTH + 1] = "\0";

    while (!list_end)
    {

        char last_char = fgetc(stream_s);

        switch (last_char)
        {

        case -1:
            error_exit(parserSyntaxError, "Graph is not finished, unexpected 'EOF'\n");
            break;

        case '\n':
        case '\r':
            if (strlen(node_name) != 0 || strlen(node2_name) != 0)
            {
                error_exit(parserSyntaxError, "Unexpected 'EOL' at position %i:%i\n", lines, columns);
            }
            lines++;
            columns = 0;
            break;

        case '{':
            if (list_start)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            list_start = true;
            break;

        case '}':
            if (!list_start || edge_start)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            list_end = true;
            break;

        case '(':
            if (!list_start || edge_start || !list_split)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            edge_start = true;
            list_split = false;
            break;

        case ')':
            if (!list_start || !edge_start || !edge_split || strlen(node2_name) == 0)
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            edge_end = true;
            break;

        case ',':
            if (!list_start || edge_split || list_split || (edge_start && strlen(node_name) == 0))
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }
            if (edge_start)
            {
                edge_split = true;
            }
            else
            {
                list_split = true;
            }
            break;

        default:
            if (!list_start || !edge_start || !((last_char >= 'a' && last_char <= 'z') || (last_char >= 'A' && last_char <= 'Z') || (last_char >= '0' && last_char <= '9')))
            {
                error_exit(parserSyntaxError, "Unexpected '%c' at position %i:%i\n", last_char, lines, columns);
            }

            if (strlen(node_name) == MAX_NODE_NAME_LENGTH || strlen(node2_name) == MAX_NODE_NAME_LENGTH)
            {
                error_exit(parserNodeNameLengthOverflowError, "Node name lenght overflow (max %i characters) at position %i:%i\n", MAX_NODE_NAME_LENGTH, lines, columns);
            }

            if (!edge_split)
            {
                node_name[strlen(node_name)] = last_char;
            }
            else
            {
                node2_name[strlen(node2_name)] = last_char;
            }
            break;
        }

        if (edge_end && strlen(node_name) != 0 && strlen(node2_name) != 0)
        {
            graph_create_edge(node_name, node2_name);
            for (int i = 0; i < (int)strlen(node_name); i++)
            {
                node_name[i] = '\0';
            }
            for (int i = 0; i < (int)strlen(node2_name); i++)
            {
                node2_name[i] = '\0';
            }
            edge_start = false;
            edge_split = false;
            edge_end = false;
        }

        columns++;
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

    parse_node_data();

    parse_edge_data();
}
