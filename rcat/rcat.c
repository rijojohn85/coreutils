#include "../helpers/helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_args(Arguments *arg);
void read_stdin();
void print_line(char *line, int line_no);

const char *version = "rcat 0.0.1";
bool si, a, b, E, n, s, T, v = false;

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

int main(int argc, char *args[]) {
  if (argc > 1) {
    Arguments *arg = get_args(options, argc, args, version, length);

    if (*(arg->arguments)) {
      si = true;
      read_stdin();
    }

    if (*(arg->arguments)) {
      si = true;
      read_stdin();
    }

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
