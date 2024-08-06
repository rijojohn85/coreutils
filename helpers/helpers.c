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

Arguments *new_arguments() {
  Arguments *ret_value = (Arguments *)malloc(sizeof(Arguments));
  if (ret_value == NULL) {
    printf("Malloc error.\n");
    exit(EXIT_FAILURE);
  }
  ret_value->arguments = NULL;
  return ret_value;
}

Arguments *get_args(Options *options, int argc, char *args[],
                    const char *version, int opt_len) {

  bool *arguments = malloc(opt_len * sizeof(bool));

  Arguments *ret_value = new_arguments();
  ret_value->arguments = arguments;
  int file_counter = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(args[i], "\0") == 0) {
      break;
    }
    if ((strcmp(args[i], "-h") == 0) || strcmp(args[i], "--help") == 0) {
      *(ret_value->arguments + 1) = true;
      return ret_value;
    } else if ((strcmp(args[i], "--version") == 0)) {
      printf("%s\n", version);
      free_arg(ret_value);
      exit(EXIT_SUCCESS);
    } else {
      if (strncmp(args[i], "--", 2) == 0) {
        for (int j = 0; j < opt_len; j++) {
          if (strcmp(options[j].alt_inpt, args[i]) == 0)
            *(ret_value->arguments + j) = true;
        }
      } else if ((strncmp(args[i], "-", 1) == 0) && strlen(args[i]) > 1) {
        for (int k = 1; k < (int)strlen(args[i]); k++) {
          for (int j = 0; j < opt_len; j++) {
            // printf("%c", args[i][k]);
            if (*options[j].search_char == args[i][k]) {
              *(ret_value->arguments + j) = true;
              break;
            }
          }
        }
      } else if ((strcmp(args[i], "-") == 0)) {
        *(ret_value->arguments + 0) = true;
      } else {
        *(ret_value->files + file_counter) = args[i];
        file_counter++;
      }
    }
  }
  ret_value->file_number = file_counter;
  return ret_value;
}

void free_arg(Arguments *arg) {
  free(arg->arguments);
  free(arg);
}
