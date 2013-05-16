/*
 * Sample solution to Assignment #1, SENG 265, Spring 2013
 * "s265fmt.c"
 *
 * Copyright 2013 Michael Zastre (University of Victoria)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/*
 * Some constants
 */

#define MAX_LINES 3000000
#define MAX_LINE_LENGTH 120
#define FMT_OFF 0
#define FMT_ON 1
#define TRUE 1
#define FALSE 0


/*
 * Prototypes
 */

void chomp(char line[]);
void format_file(FILE *);
void output_word(char *);
void output_margin();
void flush_line(char *);


/*
 * Globals
 */

int page_width = 0;
int margin_width = 0;
int mode = FMT_OFF;
int newline_pending = FALSE;
int output_line_length = 0;


/*
 * Assumes the newline characters to be removed are
 * at the end the line (i.e., '\n' in between
 * regular chars will not be removed).
 */
void chomp(char line[]) {
	assert (line != NULL);

	if (strlen(line) == 0) {
		return;
	}

	while (line[strlen(line)-1] == '\n') {
		line[strlen(line)-1] = '\0';
	}

	return;	
}


void format_file(FILE *infile) {
	char buffer[MAX_LINE_LENGTH+1];
	char *t;
	
	assert (infile != NULL);

	while (fgets(buffer, MAX_LINE_LENGTH, infile)) {
		chomp(buffer);
		if (strncmp(buffer, "?pgwdth ", 8) == 0) {
			sscanf(buffer, "?pgwdth %d", &page_width);
			mode = FMT_ON;
			continue;
		} else if (strncmp(buffer, "?mrgn ", 6) == 0) {
			sscanf(buffer, "?mrgn %d", &margin_width);
			continue;
		} else if (strcmp(buffer, "?fmt on") == 0 ) {
			mode = FMT_ON;	
			continue;
		} else if (strcmp(buffer, "?fmt off") == 0 ) {
			mode = FMT_OFF;	
			continue;
		}

		/* If we reach this far, we have a regular line. */
		if (mode == FMT_OFF) {
			flush_line(buffer);
			continue;
		}

		/* If we reach this far, we have a regular line that
		 * requires formatting. Is it a blank line? If so, we
		 * need to flush the previous line and insert the
		 * blank line itself.
		 */
		if (buffer[0] == '\0') {
			flush_line("");
		}

		t = strtok(buffer, " ");
		while (t) {
			output_word(t);
			t = strtok(NULL, " ");
		}
	}
	flush_line(NULL);
}


/*
 * The purpose of this function is to format the words that have
 * been read so far, have not yet been output, and which constitute
 * (in effect) the end of a paragraph.
 */

void flush_line(char *line) {
	if (newline_pending) {
		printf("\n");
		newline_pending = FALSE;
	}

	if (line != NULL && line[0] == '\0') {
		printf("\n");
		output_line_length = 0;
	} else if (line != NULL) {
		output_margin();
		printf("%s\n", line);
		output_line_length = 0;	
	}
}


/*
 * This function contains the line-break logic. Note that this
 * function is called recursively in the case that a word causes
 * a line break.
 */

void output_word(char *word) {
	if (newline_pending == FALSE) {
		output_margin();
		newline_pending = TRUE;
		printf("%s", word);
		output_line_length = strlen(word);
		return;
	}

	if (output_line_length + 1 + strlen(word) <= page_width - margin_width) {
		output_line_length += 1 + strlen(word);
		printf(" %s", word);
	} else {
		printf("\n");
		newline_pending = FALSE;
		output_word(word);
	}
}


void output_margin() {
	int i;

	if (mode == FMT_OFF) {
		return;
	}

	for (i = 0; i < margin_width; i++) {
		printf( " " );
	}
}


int main(int argc, char *argv[]) {
	char *infile_name;
	FILE *infile;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <filename\n", argv[0]);
		exit(1);
	}

	infile_name = argv[1];

	infile = fopen(infile_name, "r");
	if (infile == NULL) {
		fprintf(stderr, "%s cannot open file named %s\n", argv[0], infile_name);
		exit(1);
	}

	format_file(infile);

	fclose(infile);

    return (0);
}
