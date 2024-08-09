#include "../helpers/helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_args(Arguments *arg);
void read_stdin();
void cat_function(Arguments *arg);
void print_line(Arguments *arg, char *line, size_t prev_len);
char *add_non_print(char *line, Arguments *arg);

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
char *add_non_print(char *line, Arguments *arg) {
  char *buf = NULL;
  size_t buf_size = sizeof(char) * 4;
  size_t pos = 0;
  char c;
  buf = malloc(buf_size);
  // create a new buffer and add chars to that;
  while (*line) {
    if (pos == buf_size - 4) { //-1 for the null terminator.
      buf_size *= 4;
      char *new_buf = realloc(buf, buf_size);
      if (new_buf == NULL) {
        free(buf); // bail on error
        perror("Error in realloc\n");
        exit(EXIT_FAILURE);
      }
      buf = new_buf; // successful realloc
    }
    // buf[pos++] = c; // add the byte onto the buffer
    if ((unsigned char)*line < 32 || (unsigned char)*line == 127) {
      if (*(arg->arguments + 2) || *(arg->arguments + 4) ||
          *(arg->arguments + 8) || *(arg->arguments + 9) ||
          *(arg->arguments + 11)) {
        if (*(arg->arguments + 2) || *(arg->arguments + 8) ||
            *(arg->arguments + 9)) {
          if (*line == '\t') {

            buf[pos++] = '^';
            buf[pos++] = 'I';
            line++;
            continue;
          }
        }
        if ((*(arg->arguments + 2) || *(arg->arguments + 4) ||
             *(arg->arguments + 8) || *(arg->arguments + 11)) &&
            (*line != '\t')) {
          buf[pos++] = '^';
          buf[pos++] = 'M';
          line++;
          continue;
        }
        buf[pos++] = *line;
      } else {
        buf[pos++] = *line;
      }
    } else {
      buf[pos++] = *line;
    }
    line++;
  }
  // shrink to fit
  if (pos < buf_size - 2) {
    char *new_buf = realloc(buf, pos + 2); //+1 for the null terminator
    if (new_buf == NULL) {
      free(buf); // bail on error
      perror("Error in realloc\n");
      exit(EXIT_FAILURE);
    }
    buf = new_buf; // successful realloc
  }
  if (*(arg->arguments + 2) || *(arg->arguments + 4) || *(arg->arguments + 5)) {
    buf[pos++] = '$';
  }
  // Add the nul terminator
  buf[pos] = '\0';
  return buf;
}

void print_line(Arguments *arg, char *line, size_t prev_len) {
  size_t len = strlen(line);
  if ((len == 0) && (prev_len == 0) && (*(arg->arguments + 7) == true)) {
    return;
  }
  if ((*(arg->arguments + 6) == true) && *(arg->arguments + 3) == false) {
    char *s = add_non_print(line, arg);
    printf("\t%d %s\n", line_no, s);
    free(s);
    line_no++;
  } else if (*(arg->arguments + 3) && len > 0) {

    char *s = add_non_print(line, arg);
    printf("\t%d %s\n", line_no, s);
    free(s);
    line_no++;
  } else if (*(arg->arguments + 3) && len == 0) {
    printf("\n");
  } else {

    char *s = add_non_print(line, arg);
    printf("%s\n", s);
    free(s);
    line_no++;
  }
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
    printf("File: %s\n", (char *)(arg->files[i]));
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
  char *line = NULL;
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
      fprintf(stderr, "Error: file %s not found\n", (char *)arg->files[i]);
      free_arg(arg);
      exit(EXIT_FAILURE);
    }
    while ((st_in = readline(fp)) != NULL) {
      len = strlen(st_in);
      print_line(arg, st_in, prev_len);
      prev_len = len;
      free(st_in);
    }
  }

  fclose(fp);
}
