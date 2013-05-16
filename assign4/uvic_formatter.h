struct Results format_lines(char **lines, int *num_lines);
struct Results format_file(FILE *infile);

struct Results {
  int size;
  char **data;
};