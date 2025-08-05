#define _GNU_SOURCE

#include "s21_grep.h"
void execute_grep(CommandFlags flags, const char *filename, regex_t *regex) {
  char *line = NULL;
  size_t line_length = 0;
  int line_count = 0, match_count = 0;
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    if (!flags.suppress_errors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory", filename);
    }
  } else {
    while (getline(&line, &line_length, file) != -1) {
      int match = !regexec(regex, line, 0, NULL, 0);
      line_count++;
      match_count += (match + flags.invert_match) % 2;

      if ((match && !flags.invert_match) || (!match && flags.invert_match)) {
        if (!flags.count_only && !flags.list_files) {
          if (flags.show_only_match) {
            handle_match(flags, regex, line, filename, line_count);
          } else {
            if (!flags.no_filenames) printf("%s:", filename);
            if (flags.line_numbers) printf("%d:", line_count);
            printf("%s", line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
          }
        }
      }
    }

    if (flags.count_only && !flags.list_files) {
      if (!flags.no_filenames) printf("%s:", filename);
      printf("%d\n", match_count);
    }
    if (flags.list_files && match_count > 0) printf("%s\n", filename);

    free(line);
    fclose(file);
  }
}

int main(int argc, char **argv) {
  int error = 0;
  PatternList patterns = {};
  CommandFlags flags = {};
  regex_t regex;

  error = process_arguments(argc, argv, &patterns, &flags);
  if (argc - optind == 1) flags.no_filenames = 1;

  if (!error) {
    if (flags.ignore_case) {
      error = regcomp(&regex, patterns.data, REG_EXTENDED | REG_ICASE);
    } else {
      error = regcomp(&regex, patterns.data, REG_EXTENDED);
    }
  }

  if (!error) {
    for (int i = optind; i < argc; i++) {
      execute_grep(flags, argv[i], &regex);
    }
    regfree(&regex);
  }
  if (patterns.data) free(patterns.data);

  return error;
}

int process_arguments(int argc, char **argv, PatternList *patterns,
                      CommandFlags *flags) {
  int opt, error = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1 && !error) {
    switch (opt) {
      case 'e':
        flags->use_regex = 1;
        error = append_pattern(optarg, patterns, *flags);
        break;
      case 'i':
        flags->ignore_case = 1;
        break;
      case 'v':
        flags->invert_match = 1;
        break;
      case 'c':
        flags->count_only = 1;
        break;
      case 'l':
        flags->list_files = 1;
        break;
      case 'n':
        flags->line_numbers = 1;
        break;
      case 'h':
        flags->no_filenames = 1;
        break;
      case 's':
        flags->suppress_errors = 1;
        break;
      case 'f':
        flags->file_patterns = 1;
        error = append_patterns_from_file(optarg, patterns, *flags);
        break;
      case 'o':
        flags->show_only_match = 1;
        break;
      default:
        break;
    }
  }

  if (!error) {
    if (patterns->size == 0 && argv[optind] != NULL) {
      append_pattern(argv[optind], patterns, *flags);
      optind++;
    }
  }

  if (optind >= argc) {
    error = 1;
    if (!flags->suppress_errors) fprintf(stderr, "s21_grep: Provide filename");
  }

  return error;
}

void handle_match(CommandFlags flags, regex_t *regex, const char *line,
                  const char *filename, int line_count) {
  regmatch_t match;
  size_t offset = 0;

  while (offset < strlen(line)) {
    if (regexec(regex, line + offset, 1, &match, 0) != 0) {
      break;
    }
    if (match.rm_eo > 0) {
      if (!flags.no_filenames) printf("%s:", filename);
      if (flags.line_numbers) printf("%d:", line_count);

      for (int i = match.rm_so; i < match.rm_eo; i++) {
        putchar(line[offset + i]);
      }
      putchar('\n');
      offset += match.rm_eo;
    } else {
      offset++;
    }
  }
}

int append_pattern(const char *pattern, PatternList *patterns,
                   CommandFlags flags) {
  int error = 0;
  size_t pattern_length = strlen(pattern);

  if (patterns->size == 0) {
    patterns->data = malloc((3 + pattern_length) * sizeof(char));

    if (patterns->data != NULL) {
      patterns->size = 3 + pattern_length;
      patterns->data[0] = '\0';
      strcat(patterns->data, "(");
      strcat(patterns->data, pattern);
      strcat(patterns->data, ")");
    } else {
      error = 1;
      if (!flags.suppress_errors) fprintf(stderr, "Failed to allocate memory");
    }
  } else {
    patterns->data =
        realloc(patterns->data, patterns->size + pattern_length + 3);
    if (patterns->data != NULL) {
      strcat(patterns->data, "|(");
      strcat(patterns->data, pattern);
      strcat(patterns->data, ")");
    } else {
      error = 1;
      if (!flags.suppress_errors) fprintf(stderr, "Failed to allocate memory");
    }
  }

  return error;
}

int append_patterns_from_file(const char *filepath, PatternList *patterns,
                              CommandFlags flags) {
  int error = 0;
  char *line = NULL;
  size_t line_length = 0;
  FILE *file = fopen(filepath, "r");

  if (file != NULL) {
    while (getline(&line, &line_length, file) != -1) {
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      append_pattern(line, patterns, flags);
    }
    free(line);
    fclose(file);
  } else {
    error = 1;
    if (!flags.suppress_errors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory", filepath);
    }
  }

  return error;
}
