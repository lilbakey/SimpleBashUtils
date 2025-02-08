#ifndef S21_CAT_H
#define S21_CAT_H

#define BASE_OPTIONS "beEnstT"
#include "../common/utils.h"

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int new_file;
} OPTIONS;

static struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                       {"number", no_argument, 0, 'n'},
                                       {"squeeze-blank", no_argument, 0, 's'},
                                       {0, 0, 0, 0}};

void print_file(FILE *pfile, OPTIONS *options, int *count_line);
void parser_flags(int argc, char **argv, OPTIONS *options);
FILE *read_file(char *path);
void output(OPTIONS *options, char *line, int length_line, int *count_line,
            int *empty_line);
void nonprintable_output(char symb);

#endif