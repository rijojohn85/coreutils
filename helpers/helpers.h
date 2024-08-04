#ifndef HELPERS
#define HELPERS
typedef struct {
  char *input;
  char *alt_inpt;
  char *help_text;
} Options;
/*
 * prints help output of the program
 */
void print_help(Options *options, char *example_usage, char *useage,
                int length);
#endif
