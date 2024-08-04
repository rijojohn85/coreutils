#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help(Options *options, char *examples, char *useage, int length) {
  printf("%s\n", useage);
  for (int i = 0; i < length; i++) {
    printf("%s,\t%s\n\t%s\n\n", options[i].input, options[i].alt_inpt,
           options[i].help_text);
  }
  printf("%s", examples);
}
bool *get_args(Options *options, int argc, char *args[], char *version,
               int opt_len) {

  bool *arguments = malloc(opt_len * sizeof(bool));

  for (int i = 1; i < argc; i++) {
    if (strcmp(args[i], "\0") == 0) {
      break;
    }
    if ((strcmp(args[i], "-h") == 0) || strcmp(args[i], "--help") == 0) {
      *(arguments + 10) = true;
      return arguments;
    } else if ((strcmp(args[i], "--version") == 0)) {
      printf("%s\n", version);
      exit(EXIT_SUCCESS);
    } else {

      printf("Arguments: %s\n", args[i]);
    }
  }
  return arguments;
}
