#ifndef S21_CAT_H
#define S21_CAT_H
#include <getopt.h>
#include <stdio.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flags;
struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                {"number", no_argument, NULL, 'n'},
                                {"squeeze-blank", no_argument, NULL, 's'},
                                {"show-nonprinting", no_argument, NULL, 'v'},
                                {"show-ends", no_argument, NULL, 'e'},
                                {"show-tabs", no_argument, NULL, 't'},
                                {0, 0, 0, 0}};
extern struct option long_options[];

int parse_arguments(int argc, char **argv, flags *options);
void print_file_content(char *filename, flags options);

#endif /* S21_CAT_H */
