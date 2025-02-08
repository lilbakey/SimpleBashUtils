#include "s21_grep.h"

int main(int argc, char **argv) {
  int exit = EXIT_SUCCESS;
  FILE *pfile = NULL;
  OPTIONS options = {0};
  int count_line = 0;

  parser_flags(argc, argv, &options);
  for (int i = optind; i < argc; i++) {
    pfile = read_file(argv[i], &options);
    printing(pfile, options, &count_line, argv[i]);
    if (i < argc - 1) {
      count_line = 0;
    }
  }
  if (options.c && !count_line && !options.l) {
    exit = EXIT_FAILURE;
  }
  return exit;
}

void parser_flags(int argc, char **argv, OPTIONS *options) {
  int option = 0;

  while ((option = getopt(argc, argv, BASE_OPTIONS)) != -1) {
    switch (option) {
      case 'e':
        options->e = 1;
        add_pattern(options, optarg);
        break;
      case 'i':
        options->i = REG_ICASE;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->c = 1;
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        regular_from_file(options, optarg);
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        error_message("Error usage!");
        break;
    }
  }
  if (options->len_pattern == 0) {
    add_pattern(options, argv[optind++]);
  }
  if (argc - optind == 1) {
    options->h = 1;
  } else if (argc - optind > 1) {
    options->files = argc - optind;
  }
}

FILE *read_file(char *path, const OPTIONS *options) {
  FILE *pfile = fopen(path, "r");
  if (pfile == NULL && !options->s) {
    error_message("File not found");
  } else if (pfile == NULL && options->s) {
    exit(EXIT_FAILURE);
  }
  return pfile;
}

int reg_result(char *string, char *pattern, int cflag, size_t nmatch,
               regmatch_t *match, int eflag) {
  int result = 0;
  regex_t regex;
  int error = regcomp(&regex, pattern, cflag);
  if (error) error_message("Error!");
  result = regexec(&regex, string, nmatch, match, eflag);
  regfree(&regex);
  return result;
}

void printing(FILE *pfile, OPTIONS options, int *count_line, char *path) {
  char *line = NULL;
  size_t size = 0;
  int length_line = 0;
  int counter_line = 1;
  regex_t regex;
  regcomp(&regex, options.pattern, REG_EXTENDED | options.i);

  length_line = getline(&line, &size, pfile);
  while (length_line != -1) {
    output_line(options, line, length_line, counter_line, count_line, path,
                &regex);
    counter_line++;
    length_line = getline(&line, &size, pfile);
  }
  regfree(&regex);
  free(line);

  if (options.c && !options.l) {
    if (!options.h) printf("%s:", path);
    printf("%d\n", *count_line);
  } else if (options.l || (*count_line && !options.files)) {
    printf("%s\n", path);
  }

  fclose(pfile);
}

void output_line(OPTIONS options, char *line, int length_line, int counter_line,
                 int *count_line, char *path, regex_t *regex) {
  int result =
      reg_result(line, options.pattern, REG_EXTENDED | options.i, 0, NULL, 0);

  if (((options.c && !result) && !options.v) || options.l) {
    ++*count_line;
  } else if (options.c && options.v && result) {
    ++*count_line;
  } else if ((!result && !options.v) || (result && options.v)) {
    if (options.files && !options.h) printf("%s:", path);
    if (options.n) printf("%d:", counter_line);
    if (options.o) {
      find_match(regex, line);
    } else {
      for (int i = 0; i < length_line; i++) {
        putchar(line[i]);
      }
    }
    if (line[length_line - 1] != '\n') putchar('\n');
  }
}

void add_pattern(OPTIONS *options, char *pattern) {
  if (options->len_pattern != 0) {
    strcat(options->pattern + options->len_pattern, "|");
    options->len_pattern++;
  }
  options->len_pattern +=
      sprintf(options->pattern + options->len_pattern, "(%s)", pattern);
}

void regular_from_file(OPTIONS *options, char *path) {
  FILE *pfile = read_file(path, options);

  char *line = NULL;
  size_t size = 0;
  int length_line = 0;

  length_line = getline(&line, &size, pfile);
  while (length_line != -1) {
    add_pattern(options, line);
    length_line = getline(&line, &size, pfile);
  }
  free(line);
  fclose(pfile);
}

void find_match(regex_t *regex, char *line) {
  regmatch_t match;
  int step = 0;

  while (1) {
    int result = regexec(regex, line + step, 1, &match, 0);
    if (!result) break;

    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    step += match.rm_eo;
  }
}
