#ifndef COMPRESS_H
#define COMPRESS_H
#include "hashmap.c/hashmap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>

struct letter_count {
  wchar_t c;
  int count;
};

// functions
FILE *open_file(char *file_name);
bool letter_iter(const void *item, void *udata);
uint64_t letter_hash(const void *item, uint64_t seed0, uint64_t seed1);
int letter_compare(const void *a, const void *b, void *udata);
void insert_into_map(wchar_t c, struct hashmap *map);
struct hashmap *get_char_count(FILE *fp);

#endif
