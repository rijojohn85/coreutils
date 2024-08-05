#include "../helpers/helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_args(Arguments *arg);

const char *version = "rcat 0.0.1";
bool a, b, E, n, s, T, v = false;

char *examples =
    "EXAMPLES\ncat f - g\n\tOutput f's contents, then standard input, then g's "
    "contents.\ncat\n\tCopy standard input to standard output.";
char *useage =
    "Usage: gcat [OPTION]... [FILE]...\n\nConcatenate FILE(s) to standard "
    "output.\n\nWith no FILE, or when FILE is -, read standard input.\n";
Options options[] = {
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
    {"-h", "--help", "displays this help and exit.", "h"},
    {"--version", "", "output version information and exit", ""}

};
int length = sizeof(options) / sizeof(options[0]);

int main(int argc, char *args[]) {
  char *st_in = NULL;
  size_t len = 0;
  ssize_t bytes_read;
  if (argc > 1) {
    Arguments *arg = get_args(options, argc, args, version, length);
    print_args(arg);

    free(arg->arguments);
    free(arg);
  } else {
    bytes_read = getline(&st_in, &len, stdin);
    if (bytes_read != -1) {
      printf("%s", st_in);
    }
  }
  free(st_in);
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
