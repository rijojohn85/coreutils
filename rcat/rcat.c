#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *args[]) {
  if (argc > 1) {
    for (int i = 1; i <= argc; i++) {
      printf("Argument %s\n", args[i]);
    }
  }
  return EXIT_SUCCESS;
}
