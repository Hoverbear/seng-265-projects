/*
 * UVic SENG 265, Fall 2011, A#4
 *
 * This will contain a solution to s265fmt3. In order to complete the
 * task of formatting a file, it must open the file and pass the result
 * to a routine in uvic_formatter.c.  That routine will then return a
 * list of strings to be output to the console/terminal, but that output
 * must be generated in this module (even if the lines are generated
 * via code in uvic_formatter.c).
 */

#include <stdio.h>
#include <stdlib.h>
#include "uvic_formatter.h"

int main(int argc, char *argv[]) {
#ifdef DEBUG
    int num_lines;
    int i;
    char **result;;

    result = format_lines(NULL, &num_lines);
    for (i = 0; i < num_lines; i++, result++) {
        printf("%d: %s\n", i+1, *result);
    }
#endif
	exit(0);
}
