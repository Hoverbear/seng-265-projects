#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Results {
  int size;
  char **data;
};

struct Results format_lines(char **lines, int *num_lines);
struct Results format_file(FILE *infile);

/* Program options. These are flagged within the input file with ?fmt, ?pgwdth, ?mrgn */
int fmt = 0;    /* Off by default. */
int mrgn = 0;   /* Off by default. Cannot be less then or equal to pgwdth-20. */
int pgwdth = 0; /* Off by default. Turns on fmt if set. */

/* Detects control sequences */
int detect_control_sequence(char *line) {
  /* We need to make a copy of the string so strtok does not clobber. */
  int length = strlen(line);
  char *buffer = (char*) malloc( length * sizeof(char) );
  if (buffer == NULL) {
    fprintf(stderr, "Could not allocate any memory!");
    exit(1);
  }
  strncpy (buffer, line, length);
  /* Tokenize the string. */
  strtok (buffer, " \n");
  /* Detect a control sequence */
  /* fmt is off by default. */
  if ( !strncmp(buffer, "?fmt", length) ) {
    char* opt = strtok (NULL, " \n");
    if ( !strncmp(opt, "on", 3) ) {
      fmt = 1;
    }
    else {
      fmt = 0;
    }
    return 1;
  }
  /* mrgn is off by default. Cannot be less then or equal to pgwdth-20. Can be with an operator (+5, -5) */
  if ( !strncmp(buffer, "?mrgn", length) ) {
    char* next = strtok (NULL, " \n");
    /* Check for an operator */
    if (!strncmp(next, "+", 1)) {
      next = next + 1;
    }
    else if (!strncmp(next, "-", 1)) {
      next = next + 1;
    }
    /* By now, we know next isn't an operator */
    /* If it's a string, we should just ignore it. */
    int opt = atoi( next );
    /* mrgn must be pgwdth-20 or less. */
    if (opt >= pgwdth - 20) {
      opt = pgwdth - 20;
    }
    mrgn = opt;
    return 1;
  }
  /* Off by default. Turns on fmt if set. */
  if ( !strncmp(buffer, "?pgwdth", length) ) {
    char* next = strtok (NULL, " \n");
    int opt = atoi( next );
    pgwdth = opt;
    fmt = 1;
    return 1;
  }
  /* Clean up */
  free(buffer);
  return 0;
}


struct Results format_file(FILE *infile) {
  char buffer[512];
  int num_lines = 0;
  struct Results result;
  char **lines = malloc(sizeof(char*));
  if (lines == NULL) {
    fprintf(stderr, "Could not allocate any memory!");
    exit(1);
  }
  
  while(fgets(buffer, 512, infile)) {
    /* Expand the array of lines */
    lines = (char**) realloc(lines, (num_lines+1) * sizeof(char*) );
    if (lines == NULL) {
      fprintf(stderr, "Could not allocate any memory!");
      exit(1);
    }
    /* Prep the new line, give it just enough room, making sure to allow for the end line character. */
    lines[num_lines] = malloc( (strlen(buffer)+1) * sizeof(char));
    if (lines[num_lines] == NULL) {
      fprintf(stderr, "Could not allocate any memory!");
      exit(1);
    }
    /* Copy the new line in */
    strncpy(lines[num_lines], buffer, strlen(buffer)+1);
    
    /* Increment the number of lines so far */
    num_lines++;
  }
  
  /* Format and return the lines */
  result = format_lines(lines, &num_lines);
  return result;
}


struct Results format_lines(char **lines, int *num_lines) {
  /* We'll store our result here. */
  struct Results result;
  result.data = (char**) malloc(sizeof(char(*)));
  if (result.data == NULL) {
    fprintf(stderr, "Could not allocate any memory!");
    exit(1);
  }
  result.size = 0;
  
  /* Array indexer */
  int i;
  /* The basic idea is to walk through each line of the input (lines), stepping through each word to see if we have enough space on our current line, if so put it in there, else create a new line. */
  for (i=0; i < *num_lines; i++) {
    /* Is it a (null) line? If so we need to break. */
    if (lines[i] == NULL) {
      break;
    }
    /* Do we have a control sequence? */
    if ( detect_control_sequence(lines[i]) ) {
      continue;
    }
    /* Is formatting on? */
    else if (fmt) {
      /* TODO: Change */
      continue;
    }
    /* Formatting is off and it's not a control sequence, just stick it into the output */
    else {
      /* Resize the array of lines */
      result.data = (char**) realloc(result.data, result.size * sizeof(char*));
      if (result.data == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Allocate a new string into the new address. */
      result.data[result.size] = strdup(lines[i]);
      printf("%d should be: %s \n", result.size, lines[i]);
      printf("%d is: %s \n", result.size, result.data[result.size]);
      if (result.data[result.size] == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Needs a new line */
      result.size++;
      continue;
    }
  }
  
  printf("Size: %d \n", result.size);
  /* Print to stdout */
  for (i = 0; i < result.size; i++) {
    printf("\nPrinting line: %d \n", i);
    printf("%s", result.data[i]);
  }
  return result;
}

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
  }
  
  fclose(infile);
  exit(0);
}