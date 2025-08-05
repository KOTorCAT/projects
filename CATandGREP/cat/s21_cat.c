#include "s21_cat.h"

int main(int argc, char **argv) {
  flags options = {};
  int error = parse_arguments(argc, argv, &options);

  if (!error) {
    for (int i = optind; i < argc; i++) {
      print_file_content(argv[i], options);
    }
  }

  return error;
}

int parse_arguments(int argc, char **argv, flags *options) {
  int opt;
  while ((opt = getopt_long(argc, argv, "benstvET", long_options, NULL)) !=
         -1) {
    switch (opt) {
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
      case 'v':
        options->v = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      default:
        break;
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "Usage: s21_cat [OPTION]... [FILE]...\n");
    return 1;
  }

  return 0;
}

void print_file_content(char *filename, flags options) {
  int ch, line_number = 1, blank_lines = 0, prev_char = '\n';
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Error: Cannot open file %s\n", filename);
    return;
  }

  while ((ch = fgetc(file)) != EOF) {
    if (options.s) {
      if (prev_char == '\n' && ch == '\n') {
        blank_lines++;
        if (blank_lines > 1) {
          continue;
        }
      } else {
        blank_lines = 0;
      }
    }

    if (options.b && prev_char == '\n' && ch != '\n') {
      printf("%6d\t", line_number++);
    } else if (options.n && prev_char == '\n' && !options.b) {
      printf("%6d\t", line_number++);
    }

    if (options.e && ch == '\n') {
      putchar('$');
    }

    if (options.t && ch == '\t') {
      putchar('^');
      ch = 'I';
    }

    if (options.v) {
      if (ch < 32 && ch != '\n' && ch != '\t') {
        putchar('^');
        putchar(ch + 64);
      } else if (ch == 127) {
        putchar('^');
        putchar('?');
      } else if (ch > 127) {
        putchar('M');
        putchar('-');
        if (ch >= 128 + 32) {
          putchar(ch - 128);
        } else {
          putchar('^');
          putchar(ch - 128 + 64);
        }
      } else {
        putchar((char)ch);
      }
    } else {
      putchar((char)ch);
    }

    prev_char = ch;
  }

  fclose(file);
}
