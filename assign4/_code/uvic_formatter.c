/*
 * UVic SENG 265, Spring 2013, A#4
 *
 * This will contain the bulk of the work for the fourth assignment. It
 * provide similar functionality to the class written in Python for
 * assignment #3, but without the need to format a list of strings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uvic_formatter.h"


char **format_file(FILE *infile) {
	return NULL;
}


char **format_lines(char **lines, int *num_lines) {
	char **result = NULL;

#ifdef DEBUG
	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL) {
		return NULL;
	}

	result[0] = (char *)malloc(sizeof(char) * 80);
	if (result[0] == NULL) {
		return NULL;
	}
	strncpy(result[0], "(machine-like voice) EXTERMINATE THEM!", 79);

	result[1] = (char *)malloc(sizeof(char) * 2);
	if (result[1] == NULL) {
		return NULL;
	}
	result[1][0] = '\0';

    *num_lines = 2;
#endif

	return result;
}
