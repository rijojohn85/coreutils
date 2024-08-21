#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

const char *argp_program_bugaddress = "rijojohn85@gmail.com";
const char *argp_program_version = "rwc - 0.0.1";

static struct argp_option options[] = {
    {"hello", 'v', 0, 0, "Produce verbose output"},
};

int main(void) {
  printf("hi");
  return EXIT_SUCCESS;
}
