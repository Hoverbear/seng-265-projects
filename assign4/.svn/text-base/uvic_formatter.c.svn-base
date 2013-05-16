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

/* Program options. These are flagged within the input file with ?fmt, ?pgwdth, ?mrgn */
int fmt = 0;    /* Off by default. */
int mrgn = 0;   /* Off by default. Cannot be less then or equal to pgwdth-20. */
int pgwdth = 0; /* Off by default. Turns on fmt if set. */

/* Program state. These are used within the program. */
int current_position = 0;
int got_file = 0;

/* Detects control sequences */
int detect_control_sequence(char *line) {
  /* We need to make a copy of the string so strtok does not clobber. */
  int length = strlen(line) + 1;
  char *buffer = (char*) calloc( length, sizeof(char) );
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
    current_position = 0;
    return 1;
  }
  /* mrgn is off by default. Cannot be less then or equal to pgwdth-20. Can be with an operator (+5, -5) */
  if ( !strncmp(buffer, "?mrgn", length) ) {
    char* next = strtok (NULL, " \n");
    /* Check for an operator */
    if (!strncmp(next, "+", 1)) {
      next = next + 1;
      mrgn += atoi( next );
    }
    else if (!strncmp(next, "-", 1)) {
      next = next + 1;
      mrgn -= atoi( next );
    }
    else {
      mrgn = atoi( next );
    }
    /* By now, we know next isn't an operator */
    /* If it's a string, we should just ignore it. */
    /* mrgn must be pgwdth-20 or less. */
    if (mrgn >= pgwdth - 20) {
      mrgn = pgwdth - 20;
    }
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
  buffer = (char*) realloc( buffer, (length+1) * sizeof(char) );
  /* Clean up */
  free(buffer);
  return 0;
}


struct Results format_file(FILE *infile) {
  got_file = 1;
  char buffer[512];
  int num_lines = 0;
  struct Results result;
  char **lines = calloc(1,sizeof(char*));
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
    lines[num_lines] = calloc( (strlen(buffer)+1), sizeof(char));
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
  result.data = (char**) calloc(1,sizeof(char*));
  if (result.data == NULL) {
    fprintf(stderr, "Could not allocate any memory!");
    exit(1);
  }
  /* Initialize our data */
  result.size = 0;
  
  /* Array indexer */
  int i = 0;

  /* The basic idea is to walk through each line of the input (lines), stepping through each word to see if we have enough space on our current line, if so put it in there, else create a new line. */
  for (i=0; i < *num_lines; i++) {
    /* Array indexer */
    
    /* Is it a hard line break? */
    if (!strncmp(lines[i], "\n", 1) && fmt) {
      /*if (current_position != 0) {
        strncat (result.data[result.size], "\n", 1);
      }*/
      result.size++;
      /* Resize the array of lines, result.size+1 for the [0] element. */
      result.data = (char**) realloc(result.data, (result.size+1) * sizeof(char*));
      if (result.data == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Allocate a new string into the new address. */
      result.data[result.size] = (char*) calloc( 2, sizeof(char));
      if (result.data[result.size] == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Copy the string in */
      strncpy(result.data[result.size], "\n", 2);
      /* Ensure we increment the number of lines. Use pgwdth to coax a new line. */
      current_position = pgwdth;
      continue;
    }
    /* Do we have a control sequence? */
    else if ( detect_control_sequence(lines[i]) ) {

      /* Mutation of configuration state is handled within the function. We should just ignore the line if it passes true. */
      continue;
    }
    /* Is formatting on? */
    else if (fmt) {
      /* We need to appropriately format the line given the current configuration state. */
      /* Create space for the line to copy and work with. */
      char *buffer = (char*) calloc( strlen(lines[i]) + 1, sizeof(char) );
      if (buffer == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Copy the string in, make sure to have a space for \0 */
      strncpy (buffer, lines[i], strlen(lines[i])+1);
      /* Break up the string into words, punctuation should be grouped with words. */
      char* word = strtok (buffer, " \n");
      /* For each word (token) do some prep, then load it in. */
      while (word) {
        if (strlen(word) > pgwdth - mrgn) {
          fprintf(stderr, "A detected word was to large to fit on a given line!");
          exit(1);
        }
        /* Determine if we need to start a new line. 2 extra for a space and newline */
        if (current_position + strlen(word) + 1 > pgwdth) {
          /* Start a new line, get us in that position. */
          strncat (result.data[result.size], "\n", 2);
          result.size++;
          result.data = (char**) realloc(result.data, (result.size+1) * sizeof(char*));
          if (result.data == NULL) {
            fprintf(stderr, "Could not allocate any memory!");
            exit(1);
          }
          current_position = 0;
        }
        /* Otherwise we should make a space. */
        else if (current_position != 0){
          strncat (result.data[result.size], " ", 1);
          current_position++;
        }
        /* Did we just start a new line? */
        if (current_position == 0) {
          /* Initialize to empty, make sure to leave room for null and newline. */
          result.data[result.size] = (char*) calloc(pgwdth + 2,sizeof(char));
          if (result.data[result.size] == NULL) {
            fprintf(stderr, "Could not allocate any memory!");
            exit(1);
          }
          /* Create any margins we might need */
          int loop = 0;
          while (loop < mrgn) {
            strncat (result.data[result.size], " ", 1);
            current_position++;
            loop++;
          }
        }
        /* Put the word into the spot it goes. */
        strncat (result.data[result.size], word, strlen(word));
        current_position += strlen (word);
        word = strtok (NULL, " \n");
      }
      
      free(buffer);
      continue;
    }
    /* Formatting is off and it's not a control sequence, just stick it into the output */
    else {
      if (current_position < pgwdth && result.size > 0) {
        strncat (result.data[result.size], "\n", 2);
        result.size++;
      }
      /* Resize the array of lines, result.size+1 for the [0] element. */
      result.data = (char**) realloc(result.data, (result.size+1) * sizeof(char*));
      if (result.data == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Allocate a new string into the new address. */
      int length = strlen(lines[i])+1;
      result.data[result.size] = (char*) calloc( length, sizeof(char));
      if (result.data[result.size] == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
      /* Copy the string in */
      strncpy(result.data[result.size], lines[i], length);
      /* Ensure we increment the number of lines. */
      /*if (result.size == 0 || current_position >= pgwdth) { */
        result.size++;
        /*}*/
      current_position = pgwdth + 1;
      continue;
    }
  }
  
  /* Zastre's file output a newline at the end of fmt is on. */
  if (fmt) {
    result.size++;
    result.data = (char**) realloc(result.data, (result.size+1) * sizeof(char*));
    result.data[result.size] = (char*) calloc( 2, sizeof(char));
    strncpy(result.data[result.size], "\n", 1);
    result.size++;
  }
  
  /*int loop;
  for (loop = 0; loop < result.size; loop++) {
    fprintf(stderr, "Result [%d/%d]: %s\n", loop, result.size, result.data[loop] );
  }*/
  if (got_file) {
    for(i=0; i< *num_lines; i++) {
      free(*(lines+i));
    }
    free(lines);
  }
  return result;
}