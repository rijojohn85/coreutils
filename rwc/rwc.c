#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

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
  int bytes, chars, lines, max_line_length, word, no_files;
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
    // TODO:
    printf("argnum: %d\n", state->next);
    arguments->files = &state->argv[state->arg_num];
    state->next = state->argc;
    break;
  case ARGP_KEY_END:
    arguments->no_files = state->arg_num;
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
  printf("Files: ");
  for (int i = 0; arguments.files[i]; i++) {
    printf("%s ", arguments.files[i]);
  }
  printf("\n");
  printf("BYTES: %s\nCHARS: %s\nLINES: %s\nMAX-LINE-LENGTH: %s\nWORDS: %s\n",
         arguments.bytes ? "yes" : "no", arguments.chars ? "yes" : "no",
         arguments.lines ? "yes" : "no",
         arguments.max_line_length ? "yes" : "no",
         arguments.word ? "yes" : "no");

  exit(0);
}
