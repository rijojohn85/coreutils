#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
void print_help(Options *options, char *examples, char *useage, int length) {
  printf("%s\n", useage);
  for (int i = 0; i < length; i++) {
    printf("%s,\t%s\n\t%s\n\n", options[i].input, options[i].alt_inpt,
           options[i].help_text);
  }
  printf("%s", examples);
}

Arguments *new_arguments(int argc) {
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

  int file_counter = 0;
  bool *arguments = malloc(opt_len * sizeof(bool));
  for (int i = 0; i < opt_len; i++) {
    arguments[i] = false;
  }
  Arguments *ret_value = malloc(sizeof(*ret_value) + opt_len * sizeof(bool) +
                                sizeof(char *) * argc);

  ret_value->arguments = arguments;
  for (int i = 1; i < argc; i++) {
    bool flag = false;
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
          if (strcmp(options[j].alt_inpt, args[i]) == 0) {

            *(ret_value->arguments + j) = true;
            flag = true;
          }
        }
        if (!flag) {
          fprintf(stderr, "Invalid option %s\n", args[i]);
          free_arg(ret_value);
          exit(EXIT_SUCCESS);
        }
      } else if ((strncmp(args[i], "-", 1) == 0) && strlen(args[i]) > 1) {
        for (int k = 1; k < (int)strlen(args[i]); k++) {
          flag = false;
          for (int j = 0; j < opt_len; j++) {
            // printf("%c", args[i][k]);
            if (*options[j].search_char == args[i][k]) {
              *(ret_value->arguments + j) = true;
              flag = true;
              break;
            }
          }
          if (!flag) {
            fprintf(stderr, "Invalid option %c\n", args[i][k]);
            free_arg(ret_value);
            exit(EXIT_SUCCESS);
          }
        }
      } else if ((strcmp(args[i], "-") == 0)) {
        *(ret_value->arguments + 0) = true;
      } else {
        ret_value->files[file_counter++] = args[i];
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

char *readline(FILE *fp) {
  size_t offset = 0;  // Index next char goes in the buffer
  size_t bufsize = 4; // initial size of the buffer. preferably multiple of 2
  char *buf;          // the buffer
  int c;              // the character we are going to read.

  buf = malloc(bufsize); // allocate inital buffer

  while (c = fgetc(fp), c != '\n' && c != EOF) {
    // check if we're out of room in the buffer account for the extra byte for
    // the NULL terminator
    if (offset == bufsize - 1) { //-1 for the null terminator.
      bufsize *= 2;
      char *new_buf = realloc(buf, bufsize);
      if (new_buf == NULL) {
        free(buf); // bail on error
        perror("Error in realloc\n");
        exit(EXIT_FAILURE);
      }
      buf = new_buf; // successful realloc
    }
    buf[offset++] = c; // add the byte onto the buffer
  }
  // we hit newline or EOF
  //
  // if at EOF and we read no bytes, free the buffer and return NULL to indicate
  // we've hit EOF
  if (c == EOF && offset == 0) {
    free(buf);
    return NULL;
  }

  // shrink to fit
  if (offset < bufsize - 1) {
    char *new_buf = realloc(buf, offset + 1); //+1 for the null terminator
    if (new_buf == NULL) {
      free(buf); // bail on error
      perror("Error in realloc\n");
      exit(EXIT_FAILURE);
    }
    buf = new_buf; // successful realloc
  }
  // Add the nul terminator
  buf[offset] = '\0';
  return buf;
}
wchar_t *wreadline(FILE *fp) {
  size_t offset = 0;  // Index next char goes in the buffer
  size_t bufsize = 4; // initial size of the buffer. preferably multiple of 2
  wchar_t *buf;       // the buffer
  wint_t c;           // the character we are going to read.

  buf = malloc(bufsize); // allocate inital buffer

  while (c = fgetwc(fp), c != '\n' && c != EOF) {
    // check if we're out of room in the buffer account for the extra byte for
    // the NULL terminator

    if (offset == bufsize - 1) { //-1 for the null terminator.
      bufsize *= 2;
      wchar_t *new_buf = realloc(buf, bufsize);
      if (new_buf == NULL) {
        free(buf); // bail on error
        perror("Error in realloc\n");
        exit(EXIT_FAILURE);
      }
      buf = new_buf; // successful realloc
    }
    buf[offset++] = c; // add the byte onto the buffer
  }
  // we hit newline or EOF
  //
  // if at EOF and we read no bytes, free the buffer and return NULL to indicate
  // we've hit EOF
  if (c == EOF && offset == 0) {
    free(buf);
    return NULL;
  }
  printf("%ls\n", buf);

  // shrink to fit
  if (offset < bufsize - 1) {
    wchar_t *new_buf = realloc(buf, offset + 1); //+1 for the null terminator
    if (new_buf == NULL) {
      free(buf); // bail on error
      perror("Error in realloc\n");
      exit(EXIT_FAILURE);
    }
    buf = new_buf; // successful realloc
  }
  // Add the nul terminator
  buf[offset] = '\0';
  return buf;
}
