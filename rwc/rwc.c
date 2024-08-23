#include <argp.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

static error_t parse_opt(int key, char *arg, struct argp_state *state);

void run_process(char *file_name);
const char *argp_program_bugaddress = "rijojohn85@gmail.com";
const char *argp_program_version = "rwc - 0.0.1";
static char doc[] = "wc - print newline, word and byte counts for each file";
static char args_doc[] = "wc [OPTION] [FILE]";

/*The options we understand. */
static struct argp_option options[] = {
    {"bytes", 'c', 0, 0, "print the byte counts"},
    {"chars", 'm', 0, 0, "print the character counts"},
    {"lines", 'l', 0, 0, "print the new line counts"},
    {"max-line-length", 'L', 0, 0,
     "print the length of the longest line(wrt to chars)"},
    {"word", 'w', 0, 0, "print the word counts"},
    {0}};

struct arguments {
  int bytes, chars, lines, max_line_length, word;
  char **files;
};
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;
  switch (key) {
  case 'c':
    arguments->bytes = 1;
    break;
  case 'm':
    arguments->chars = 1;
    break;
  case 'l':
    arguments->lines = 1;
    break;
  case 'L':
    arguments->max_line_length = 1;
    break;
  case 'w':
    arguments->word = 1;
    break;
  case ARGP_KEY_ARG:
    arguments->files = &state->argv[state->next - 1];
    state->next = state->argc;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 1) {
      argp_usage(state);
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  struct arguments arguments;

  /* Default values. */
  arguments.bytes = 0;
  arguments.chars = 0;
  arguments.lines = 0;
  arguments.max_line_length = 0;
  arguments.word = 0;

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  // printf("ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\n"
  //        "VERBOSE = %s\nSILENT = %s\n",
  //        arguments.args[0], arguments.args[1], arguments.output_file,
  //        arguments.verbose ? "yes" : "no", arguments.silent ? "yes" : "no");
  for (int i = 0; arguments.files[i]; i++) {
    run_process(arguments.files[i]);
  }
  exit(EXIT_SUCCESS);
}

void run_process(char *file_name) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;

  int chars = 0;
  size_t bytes = 0;
  int lines = 0;

  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: file %s not found\n", file_name);
    exit(EXIT_FAILURE);
  }
  // while ((ch = fgetwc(fp)) != EOF) {
  //   chars++;
  //   bytes += sizeof(ch);
  //   if (ch == '\n') {
  //     lines++;
  //   }
  // }
  // printf("%d %ld %d %s", chars, (bytes / 4), lines, file_name);
  ssize_t bytes_read = 0;
  while ((bytes_read = getline(&line, &len, fp)) != -1) {
    wchar_t *wc_string = malloc(sizeof(line));
    size_t wc_len = mbstowcs(wc_string, line, strlen(line));

    printf("%ls: %zu\n", wc_string, wc_len);
    // printf("%s: %zu\n", line, strlen(line));
  }
  free(line);
  fclose(fp);
}
