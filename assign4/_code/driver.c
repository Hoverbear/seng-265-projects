/* 
 * UVic SENG 265, Spring 2013, A#4
 *
 * Code for driver.c -- Calls the "format_lines()" routine within the
 * uvic_formatter.c module.  ("format_lines()" may, of course, be called
 * from within other programs that also link in uvic_formatter.o.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uvic_formatter.h"

int main(int argc, char *argv[]) {
	char **result;
	char *lines[] = {
		"?pgewdth 30",
		"While there    are enough characters   here to",
		"fill",
		"   at least one line, there is",
		"plenty",
		"of",
		"            white space that needs to be",
		"eliminated",
		"from the original",
		"         text file."	
	};
	char **line;
    int  num_lines = 10;

	result = format_lines(lines, &num_lines);

	if (result == NULL) {
		printf("%s: it appears 'format_lines' is not yet complete\n",
			argv[0]);
		exit(1);
	}

	for (line = result; *line != NULL; line++) {
		printf ("%s\n", *line);
	}

	exit(0);
}
