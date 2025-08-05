#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t size;
} PatternList;

typedef struct {
  int use_regex;
  int ignore_case;
  int invert_match;
  int count_only;
  int list_files;
  int line_numbers;
  int no_filenames;
  int suppress_errors;
  int file_patterns;
  int show_only_match;
} CommandFlags;

int process_arguments(int argc, char **argv, PatternList *patterns,
                      CommandFlags *flags);
int handle_flag(int opt, const char *optarg, PatternList *patterns,
                CommandFlags *flags);
int append_pattern(const char *pattern, PatternList *patterns,
                   CommandFlags flags);
int append_patterns_from_file(const char *filepath, PatternList *patterns,
                              CommandFlags flags);
void execute_grep(CommandFlags flags, const char *filename, regex_t *regex);
int should_print_line(int match, CommandFlags flags);
void print_line(CommandFlags flags, const char *filename, const char *line,
                int line_count, regex_t *regex);
void handle_match(CommandFlags flags, regex_t *regex, const char *line,
                  const char *filename, int line_count);

#endif  // S21_GREP_H
