#include <stdint.h>
#include <stdio.h>
#ifndef BIT_WRITER
#define BIT_WRITER

struct BitWriter {
  FILE *file;
  uint32_t current_byte;
  uint8_t num_bits_left;
};

struct BitWriter open_bit_writer(const char *path);
void write_bits(struct BitWriter *a_writer, uint32_t bits,
                uint8_t num_bits_to_write);
void flush_bit_writer(struct BitWriter *a_writer);
void close_bit_writer(struct BitWriter *a_writer);

#endif
