/**
 * @file error.c
 * @author Marek Gergel (xgerge01)
 * @brief  
 */

#include "../include/error.h"
#include "../include/resources.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief Prints an error message, free used memory and exits the program.
 * 
 * @param errcode error exit code
 * @param msg message to print
 * @param ... message arguments
 */
void error_exit(errorCodes_t errcode, char* msg, ...) {
    fflush(stdout);
    fflush(stderr);
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, msg, args);
    va_end(args);
    FREE_RESOURCES;
    exit(errcode);
}

/**
 * @brief Prints a warning message.
 * 
 * @param msg message to print
 * @param ... message arguments
 */
void warning_print(char* msg, ...) {
    fflush(stdout);
    fflush(stderr);
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, msg, args);
    va_end(args);
}