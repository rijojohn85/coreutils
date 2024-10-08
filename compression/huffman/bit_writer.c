#include "bit_writer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t create_string_of_0s_at_left(uint8_t num_0s) {
  return 0xffff >> num_0s;
}

uint32_t unset_left_bits(uint32_t byte, uint8_t num_bits_to_unset) {
  return byte & create_string_of_0s_at_left(num_bits_to_unset);
}
struct BitWriter open_bit_writer(const char *path) {
  FILE *fp = fopen(path, "wb");
  if (fp == NULL) {
    printf("file open error\n");
    exit(EXIT_FAILURE);
  }
  struct BitWriter new = {fp, 0, 32};
  return new;
}
static void fill_current_bytes(struct BitWriter *a_writer, uint32_t bits,
                               uint8_t num_bits_to_write) {

  a_writer->current_byte = a_writer->current_byte << num_bits_to_write;
  a_writer->current_byte |= unset_left_bits(bits, 32 - num_bits_to_write);
  a_writer->num_bits_left = a_writer->num_bits_left - num_bits_to_write;
}

void write_bits(struct BitWriter *a_writer, uint32_t bits,
                uint8_t num_bits_to_write) {
  if (num_bits_to_write <= a_writer->num_bits_left) {
    fill_current_bytes(a_writer, bits, num_bits_to_write);
    if (a_writer->num_bits_left == 0) {
      flush_bit_writer(a_writer);
    }
  } else {
    uint8_t bits_to_skip = num_bits_to_write - a_writer->num_bits_left;
    a_writer->current_byte = a_writer->current_byte << a_writer->num_bits_left;
    a_writer->current_byte |=
        unset_left_bits(bits >> bits_to_skip, 32 - a_writer->num_bits_left);
    flush_bit_writer(a_writer);
    fill_current_bytes(a_writer, bits << bits_to_skip, bits_to_skip);
  }
}

void flush_bit_writer(struct BitWriter *a_writer) {
  a_writer->current_byte = 0;
  a_writer->num_bits_left = 32;
}
