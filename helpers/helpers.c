#include "helpers.h"
#include <stdio.h>

void print_help(Options *options, char *examples, char *useage, int length) {
  printf("%s\n", useage);
  for (int i = 0; i < length; i++) {
    printf("%s,\t%s\n\t%s\n\n", options[i].input, options[i].alt_inpt,
           options[i].help_text);
  }
  printf("%s", examples);
}
