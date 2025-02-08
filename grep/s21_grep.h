#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE

#define BASE_OPTIONS "e:ivclnhsf:o"
#define PATTERN_SIZE 99999

#include <regex.h>
#include <string.h>

#include "../common/utils.h"

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char pattern[PATTERN_SIZE];
  int len_pattern;
  int files;
} OPTIONS;

void parser_flags(int argc, char **argv, OPTIONS *options);
FILE *read_file(char *path, const OPTIONS *options);
void printing(FILE *pfile, OPTIONS options, int *count_line, char *path);
void output_line(OPTIONS options, char *line, int length_line, int counter_line,
                 int *count_line, char *path, regex_t *regex);
void add_pattern(OPTIONS *options, char *pattern);
void regular_from_file(OPTIONS *options, char *path);
void find_match(regex_t *regex, char *line);

#endif
