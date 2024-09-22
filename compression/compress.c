#include "compress.h"
#include <stdio.h>

FILE *open_file(char *file_name) { return fopen(file_name, "r"); }
