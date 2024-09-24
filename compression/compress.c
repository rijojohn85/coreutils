#include "compress.h"
#include "hashmap.c/hashmap.h"
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>

FILE *open_file(char *file_name) { return fopen(file_name, "r"); }
void insert_into_map(char c, struct hashmap *map) {
  struct letter_count *letter;
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = c});
  if (letter) {
    int count = letter->count;
    hashmap_set(map, &(struct letter_count){.c = c, .count = count + 1});
  } else {
    hashmap_set(map, &(struct letter_count){.c = c, .count = 1});
  }
}

uint64_t letter_hash(const void *item, uint64_t seed0, uint64_t seed1) {
  const struct letter_count *letter = item;
  return hashmap_sip(&(letter->c), sizeof(letter->c), seed0, seed1);
}

int letter_compare(const void *a, const void *b, void *udata) {
  const struct letter_count *ua = a;
  const struct letter_count *ub = b;
  if (ua->c < ub->c) {
    return -1;
  } else if (ua->c == ub->c) {
    return 0;
  } else {
    return 1;
  }
}

struct hashmap *get_char_count(FILE *fp) {
  (void)fp;
  struct hashmap *map = hashmap_new(sizeof(struct letter_count), 0, 0, 0,
                                    letter_hash, letter_compare, NULL, NULL);
  int c;
  while ((c = fgetc(fp)) != EOF) {
    insert_into_map(c, map);
  }
  return map;
}
