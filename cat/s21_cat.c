#include "s21_cat.h"

int main(int argc, char *argv[]) {
  FILE *pfile = NULL;
  OPTIONS options = {0};
  int count_line = 0;

  parser_flags(argc, argv, &options);
  for (int i = optind; i < argc; i++) {
    pfile = read_file(argv[i]);
    print_file(pfile, &options, &count_line);
    options.new_file = 1;
  }

  return EXIT_SUCCESS;
}

void parser_flags(int argc, char **argv, OPTIONS *options) {
  int option = 0;

  while ((option = getopt_long(argc, argv, BASE_OPTIONS, long_options, 0)) !=
         -1) {
    switch (option) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case '?':
        error_message("Error!");
        break;
      default:
        error_message("Error usage!");
        break;
    }
  }
}

FILE *read_file(char *path) {
  FILE *pfile = fopen(path, "r");
  if (pfile == NULL) {
    error_message("No such file");
  }
  return pfile;
}

void print_file(FILE *pfile, OPTIONS *options, int *count_line) {
  char *line = NULL;
  size_t size = 0;
  int length_line = 0;
  int empty_line = 0;

  length_line = getline(&line, &size, pfile);
  while (length_line != -1) {
    output(options, line, length_line, count_line, &empty_line);
    length_line = getline(&line, &size, pfile);
  }
  free(line);
  fclose(pfile);
}

void output(OPTIONS *options, char *line, int length_line, int *count_line,
            int *empty_line) {
  if (options->b) options->n = 0;

  if (!(options->s && *empty_line && line[0] == '\n')) {
    if (line[0] == '\n') {
      *empty_line = 1;
    } else {
      *empty_line = 0;
    }
    if (((options->b && line[0] != '\n') || options->n) &&
        (!options->new_file)) {
      printf("%6d\t", ++*count_line);
    }
    for (int i = 0; i < length_line; i++) {
      if (options->e && line[i] == '\n') {
        putchar('$');
      }
      if (options->t && line[i] == '\t') {
        putchar('^');
        line[i] = '\t' + 64;
      }
      if (options->v) {
        nonprintable_output(line[i]);
        continue;
      }
      putchar(line[i]);
    }
    options->new_file = 0;
  }
}

void nonprintable_output(char symb) {
  if (symb < -96) {
    putchar('M');
    putchar('-');
    putchar('^');
    symb += 192;
    putchar(symb);
  } else if (symb < 0) {
    putchar('M');
    putchar('-');
    symb += 128;
    putchar(symb);
  } else if (symb == 9 || symb == 10) {
    putchar(symb);
  } else if (symb < 32) {
    putchar('^');
    symb += 64;
    putchar(symb);
  } else if (symb < 127) {
    putchar(symb);
  } else {
    putchar('^');
    putchar('?');
  }
}