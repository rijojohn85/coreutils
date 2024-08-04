#ifndef HELPERS
#define HELPERS
#include <stdbool.h>
typedef struct {
  char *input;
  char *alt_inpt;
  char *help_text;
  char *search_char;
} Options;
/*
 * prints help output of the program
 */
void print_help(Options *options, char *example_usage, char *useage,
                int length);
bool *get_args(Options *options, int argc, char *args[], char *version,
               int opt_len);
#endif
