#ifndef HELPERS
#define HELPERS
#include <stdbool.h>
#include <stdio.h>
typedef struct {
  char *input;
  char *alt_inpt;
  char *help_text;
  char *search_char;
} Options;
typedef struct {
  bool *arguments;
  int file_number;
  char *files[];
} Arguments;

/*
 * prints help output of the program
 */
void print_help(Options *options, char *example_usage, char *useage,
                int length);
/*
 * fetches arguments and file names from input
 */
Arguments *get_args(Options *options, int argc, char *args[],
                    const char *version, int opt_len);
/*
 * frees argument variable
 */
void free_arg(Arguments *arg);
/*
 *
 * Read a line of arbitrary size from a file
 * Returns a pointer to the line.
 * Returns NULL on EOF or error.

 * It's up to the caller to free() this pointer when done with it.

 * Note that this strips the newline from the result. If you need
 *it in there, probably best to switch this to a do-while.
 */
char *readline(FILE *fp);
#endif
