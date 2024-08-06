#include "../helpers/helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_args(Arguments *arg);
void read_stdin();
void cat_function(Arguments *arg);
void print_line(Arguments *arg, char *line, size_t prev_len);
void add_num(char *line);
void add_non_print(char *line);

const char *version = "rcat 0.0.1";
int line_no = 1;
bool prev_blank = false;

char *examples =
    "EXAMPLES\ncat f - g\n\tOutput f's contents, then standard input, then g's "
    "contents.\ncat\n\tCopy standard input to standard output.";
char *useage =
    "Usage: gcat [OPTION]... [FILE]...\n\nConcatenate FILE(s) to standard "
    "output.\n\nWith no FILE, or when FILE is -, read standard input.\n";
Options options[] = {
    {"-", "", "standard input", "-"},
    {"-h", "--help", "displays this help and exit.", "h"},
    {"-A", "--show-all", "equivalent to -vET", "A"},
    {"-b", "number-nonblank", "number non empty output lines, overrides -n",
     "b"},
    {"-e", "", "equivalent to -vE", "e"},
    {"-E", "--show-ends", "display $ at the end of each line", "E"},
    {"-n", "--number", "number all output lines", "n"},
    {"-s", "--squeeze-blank", "suppress repeated empty output lines", "s"},
    {"-t", "", "equivalent to -vT", "t"},
    {"-T", "--show-tabs", "display TAB characters as ^I", "T"},
    {"-u", "", "(ignored)", "u"},
    {"-v", "--show-nonprinting", "use ^ and M- notation except for LFD and TAB",
     "v"},
    {"--version", "", "output version information and exit", ""},

};
int length = sizeof(options) / sizeof(options[0]);

void print_line(Arguments *arg, char *line, size_t prev_len) {
  if (((strlen(line) == 0) && (prev_len == 0) &&
       (*(arg->arguments + 7) == true))) {
    return;
  }
  if ((*(arg->arguments + 11)) == true && (strlen(line) > 1)) {
    add_non_print(line);
  }
  if (*(arg->arguments + 3)) {
    if (strlen(line) > 1) {
      add_num(line);
    }
  } else if ((*(arg->arguments + 6))) {
    add_num(line);
  }
  printf("%s\n", line);
}
void add_non_print(char *line) {
  // create a new buffer and add chars to that;
  size_t pos = 0;
  while (pos < strlen(line)) {
    if ((*(line + pos)) >= 'a' && (*(line + pos) <= 'Z')) {
      continue;
    }
    if ((*(line + pos) == '\n') || (*(line + pos) == '\t')) {
      continue;
    }
  }
}

void add_num(char *line) {
  char *new_line = malloc(sizeof(line) + 3);
  sprintf(new_line, "\t%d ", line_no);
  strcat(new_line, line);
  strcpy(line, new_line);
  line_no++;
  free(new_line);
}

int main(int argc, char *args[]) {
  if (argc > 1) {
    Arguments *arg = get_args(options, argc, args, version, length);
    cat_function(arg);
    // print_args(arg);
    free_arg(arg);
  } else {
    read_stdin();
  }
  return EXIT_SUCCESS;
}

void print_args(Arguments *arg) {
  for (int i = 0; i < length; i++) {
    if (*(arg->arguments + i) == true)
      printf("Option %s chosen\n", options[i].input);
  }
  for (int i = 0; i < arg->file_number; i++) {
    printf("File: %s\n", (arg->files[i]));
  }
}

void read_stdin() {
  char *st_in = NULL;
  size_t len = 0;
  ssize_t bytes_read = 0;
  while (bytes_read != -1) {
    bytes_read = getline(&st_in, &len, stdin);
    if (bytes_read != -1) {
      printf("%s", st_in);
    }
  }
  free(st_in);
}

void cat_function(Arguments *arg) {
  char *st_in;
  FILE *fp;
  size_t len, prev_len = 1;
  if (*(arg->arguments + 1)) {
    print_help(options, examples, useage, length);
    free_arg(arg);
    exit(EXIT_SUCCESS);
  }
  for (int i = 0; i < arg->file_number; i++) {
    fp = fopen(arg->files[i], "r");

    if (fp == NULL) {
      fprintf(stderr, "Error: file %s not found\n", arg->files[i]);
      free_arg(arg);
      exit(EXIT_FAILURE);
    }
    // https://beej.us/guide/bgc/html/split/manual-memory-allocation.html#reading-in-lines-of-arbitrary-length
    // need to implement this.
    while ((st_in = readline(fp)) != NULL) {

      len = strlen(st_in);
      print_line(arg, st_in, prev_len);
      prev_len = len;
    }
  }
  fclose(fp);
  free(st_in);
}
