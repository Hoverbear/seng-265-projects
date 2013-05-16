/*
 * UVic SENG 265, Fall 2011, A#4
 *
 * This will contain a solution to s265fmt3. In order to complete the
 * task of formatting a file, it must open the file and pass the result
 * to a routine in uvic_formatter.c.   That routine will then return a
 * list of strings to be output to the console/terminal, but that output
 * must be generated in this module (even if the lines are generated
 * via code in uvic_formatter.c).
 */

#include <stdio.h>
#include <stdlib.h>
#include "uvic_formatter.h"

int main(int argc, char *argv[]) {
  /* For opening file */
  char *infile_name;
  FILE *infile;
  /* For Output */
  int i;
  struct Results result;;

  /* Did they give us a filename to read? */
  if (argc < 2) {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  /* Can we open the file? If so, open it and name it infile */
  infile_name = argv[1];

  infile = fopen(infile_name, "r");
  if (infile == NULL) {
    fprintf(stderr, "%s: cannot open file named %s\n", argv[0], infile_name);
    exit(1);
  }

  /* Send the file into an array of strings, then get it formatted by uvic_formatter.c */
  result = format_file(infile);
  
  /* Print to stdout */
  for (i = 0; i < result.size; i++) {
    printf("%s", *(result.data + i));
    free(*(result.data + i));
  }
  
  fclose(infile);
  free(result.data);
  exit(0);
}
