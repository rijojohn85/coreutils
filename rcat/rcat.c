#include "../helpers/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  SHOW_ALL = 0,
  NON_BLANK,
  SHOW_ENDS_ALL,
  SHOW_ENDS,
  NUMBER,
  SQUEEZE_BLANK,
  SHOW_TABS_ALL,
  SHOW_TABS,
  U,
  SHOW_NON_PRINTING,
  HELP,
  VERSION
} arguments;
char *examples =
    "EXAMPLES\ncat f - g\n\tOutput f's contents, then standard input, then g's "
    "contents.\ncat\n\tCopy standard input to standard output.";
char *useage =
    "Usage: gcat [OPTION]... [FILE]...\n\nConcatenate FILE(s) to standard "
    "output.\n\nWith no FILE, or when FILE is -, read standard input.\n";
Options options[] = {
    {"-A", "--show-all", "equivalent to -vET"},
    {"-b", "number-nonblank", "number non empty output lines, overrides -n"},
    {"-e", "", "equivalent to -vE"},
    {"-E", "--show-ends", "display $ at the end of each line"},
    {"-n", "-number", "number all output lines"},
    {"-s", "--squeeze-blank", "suppress repeated empty output lines"},
    {"-t", "", "equivalent to -vT"},
    {"-T", "--show-tabs", "display TAB characters as ^I"},
    {"-u", "", "(ignored)"},
    {"-v", "--show-nonprinting",
     "use ^ and M- notation except for LFD and TAB"},
    {"-h", "--help", "displays this help and exit."},
    {"--version", "", "output version information and exit"}

};
int length = sizeof(options) / sizeof(options[0]);

int main(int argc, char *args[]) {
  char *st_in = NULL;
  size_t len = 0;
  ssize_t bytes_read;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp(args[i], "\0") == 0) {
        break;
      }
      if ((strcmp(args[i], options[HELP].input) == 0) ||
          strcmp(args[i], options[HELP].alt_inpt) == 0) {
        print_help(options, examples, useage, length);
        exit(EXIT_SUCCESS);
      }
    }
  } else {
    bytes_read = getline(&st_in, &len, stdin);
    if (bytes_read != -1) {
      printf("%s", st_in);
    }
  }
  free(st_in);
  return EXIT_SUCCESS;
}
