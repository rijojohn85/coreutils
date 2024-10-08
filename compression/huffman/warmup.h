
#include <stdint.h>
/*
 * convert integer to printable binary number
 */
#ifndef WARMUP_H
#define WARMUP_H

#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)                                          \
  (((i) & 0x80ll) ? '1' : '0'), (((i) & 0x40ll) ? '1' : '0'),                  \
      (((i) & 0x20ll) ? '1' : '0'), (((i) & 0x10ll) ? '1' : '0'),              \
      (((i) & 0x08ll) ? '1' : '0'), (((i) & 0x04ll) ? '1' : '0'),              \
      (((i) & 0x02ll) ? '1' : '0'), (((i) & 0x01ll) ? '1' : '0')
#define PRINTF_BINARY_PATTERN_INT16                                            \
  PRINTF_BINARY_PATTERN_INT8 PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i)                                         \
  PRINTF_BYTE_TO_BINARY_INT8((i) >> 8), PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32                                            \
  PRINTF_BINARY_PATTERN_INT16 PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i)                                         \
  PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64                                            \
  PRINTF_BINARY_PATTERN_INT32 PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i)                                         \
  PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)

/*
 * Utility function to print in binary. u8.
 */

void print_bits(uint8_t bits);

/*
 * Always returns b11111111 (0xff)
 */

uint8_t create_string_of_eight_1s();
/*
  Examples:
  ∙ create_string_of_0s_at_right(1) would return 11111110₂.
  ∙ create_string_of_0s_at_right(2) would return 11111100₂.
  ∙ create_string_of_0s_at_right(3) would return 11111000₂.
  ∙ create_string_of_0s_at_right(0) would return 11111111₂.
  ∙ create_string_of_0s_at_right(8) would return 00000000₂.
*/
uint8_t create_string_of_0s_at_right(uint8_t num_0s);
/*
  Examples:
  ∙ create_string_of_0s_at_left(1) would return 01111111₂.
  ∙ create_string_of_0s_at_left(2) would return 00111111₂.
  ∙ create_string_of_0s_at_left(3) would return 00011111₂.
  ∙ create_string_of_0s_at_left(0) would return 11111111₂.
  ∙ create_string_of_0s_at_left(8) would return 00000000₂.
*/
uint8_t create_string_of_0s_at_left(uint8_t num_0s);
/*
  Examples:
  ∙ create_string_of_1s_at_left(2) would return 11000000₂.
  ∙ create_string_of_1s_at_left(0) would return 00000000₂.
  ∙ create_string_of_1s_at_left(8) would return 11111111₂.
*/
uint8_t create_string_of_1s_at_left(uint8_t num_1s);
/*
  Examples:
  ∙ create_string_of_1s_at_right(2) would return 00000011₂.
  ∙ create_string_of_1s_at_right(0) would return 00000000₂.
  ∙ create_string_of_1s_at_right(8) would return 11111111₂.
*/
uint8_t create_string_of_1s_at_right(uint8_t num_1s);
uint8_t set_left_bits(uint8_t byte, uint8_t num_bits_to_set);
uint8_t set_right_bits(uint8_t byte, uint8_t num_bits_to_set);
uint8_t unset_left_bits(uint8_t byte, uint8_t num_bits_to_unset);
uint8_t unset_right_bits(uint8_t byte, uint8_t num_bits_to_unset);
uint8_t toggle_left_bits(uint8_t byte, uint8_t num_bits_to_toggle);
uint8_t toggle_right_bits(uint8_t byte, uint8_t num_bits_to_toggle);
#endif
