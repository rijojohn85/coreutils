#include "warmup.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint8_t create_string_of_eight_1s() {
  // This function always returns 11111111₂.

  return 0xff;
}

uint8_t create_string_of_0s_at_left(uint8_t num_0s) {
  // Examples:
  // ∙ create_string_of_0s_at_left(1) would return 01111111₂.
  // ∙ create_string_of_0s_at_left(2) would return 00111111₂.
  // ∙ create_string_of_0s_at_left(3) would return 00011111₂.
  // ∙ create_string_of_0s_at_left(0) would return 11111111₂.
  // ∙ create_string_of_0s_at_left(8) would return 00000000₂.

  return 0xff >> num_0s;
}

uint8_t create_string_of_0s_at_right(uint8_t num_0s) {
  // Examples:
  // ∙ create_string_of_0s_at_right(1) would return 11111110₂.
  // ∙ create_string_of_0s_at_right(2) would return 11111100₂.
  // ∙ create_string_of_0s_at_right(3) would return 11111000₂.
  // ∙ create_string_of_0s_at_right(0) would return 11111111₂.
  // ∙ create_string_of_0s_at_right(8) would return 00000000₂.

  return (uint8_t)(0xff << num_0s);
}

uint8_t create_string_of_1s_at_left(uint8_t num_1s) {
  // Examples:
  // ∙ create_string_of_1s_at_left(2) would return 11000000₂.
  // ∙ create_string_of_1s_at_left(0) would return 00000000₂.
  // ∙ create_string_of_1s_at_left(8) would return 11111111₂.

  return (uint8_t)(0xff << (8 - num_1s));
}

uint8_t create_string_of_1s_at_right(uint8_t num_1s) {
  // Examples:
  // ∙ create_string_of_1s_at_right(2) would return 00000011₂.
  // ∙ create_string_of_1s_at_right(0) would return 00000000₂.
  // ∙ create_string_of_1s_at_right(8) would return 11111111₂.

  return (uint8_t)(0xff >> (8 - num_1s));
}

uint8_t set_left_bits(uint8_t byte, uint8_t num_bits_to_set) {
  // Examples:
  // ∙ set_left_bits(00000000₂, 2) would return 11000000₂.
  // ∙ set_left_bits(00001010₂, 2) would return 11001010₂.
  // ∙ set_left_bits(10101010₂, 2) would return 11101010₂.
  // ∙ set_left_bits(10101010₂, 0) would return 10101010₂.
  // ∙ set_left_bits(11111111₂, 0) would return 11111111₂.
  // ∙ set_left_bits(10101010₂, 8) would return 11111111₂.

  return byte | create_string_of_1s_at_left(num_bits_to_set);
}

uint8_t set_right_bits(uint8_t byte, uint8_t num_bits_to_set) {
  // Examples:
  // ∙ set_right_bits(00000000₂, 2) would return 00000011₂.
  // ∙ set_right_bits(00001010₂, 2) would return 00001011₂.
  // ∙ set_right_bits(10101010₂, 2) would return 10101011₂.
  // ∙ set_right_bits(10101010₂, 0) would return 10101010₂.
  // ∙ set_right_bits(11111111₂, 0) would return 11111111₂.
  // ∙ set_right_bits(10101010₂, 8) would return 11111111₂.

  return byte | create_string_of_1s_at_right(num_bits_to_set);
}

uint8_t unset_left_bits(uint8_t byte, uint8_t num_bits_to_unset) {
  // Examples:
  // ∙ unset_left_bits(00111111₂, 2) would return 00111111₂.
  // ∙ unset_left_bits(11110101₂, 2) would return 00110101₂.
  // ∙ unset_left_bits(01010101₂, 2) would return 00010101₂.
  // ∙ unset_left_bits(01010101₂, 1) would return 01010101₂.
  // ∙ unset_left_bits(00000000₂, 1) would return 00000000₂.
  // ∙ unset_left_bits(01010101₂, 8) would return 00000000₂.

  return byte & create_string_of_0s_at_left(num_bits_to_unset);
}

uint8_t unset_right_bits(uint8_t byte, uint8_t num_bits_to_unset) {
  // Examples:
  // ∙ unset_right_bits(11111111₂, 2) would return 11111100₂.
  // ∙ unset_right_bits(11110101₂, 2) would return 11110100₂.
  // ∙ unset_right_bits(01010101₂, 2) would return 01010100₂.
  // ∙ unset_right_bits(01010101₂, 1) would return 01010100₂.
  // ∙ unset_right_bits(00000000₂, 1) would return 00000000₂.
  // ∙ unset_right_bits(01010101₂, 8) would return 00000000₂.

  return byte & create_string_of_0s_at_right(num_bits_to_unset);
}

uint8_t toggle_left_bits(uint8_t byte, uint8_t num_bits_to_toggle) {
  // Examples:
  // ∙ toggle_left_bits(11111111₂, 2) would return 00111111₂.
  // ∙ toggle_left_bits(01011111₂, 4) would return 10101111₂.

  return byte ^ (create_string_of_1s_at_left(num_bits_to_toggle));
}

uint8_t toggle_right_bits(uint8_t byte, uint8_t num_bits_to_toggle) {
  // Examples:
  // ∙ toggle_right_bits(11111111₂, 2) would return 00111100₂.
  // ∙ toggle_right_bits(11110101₂, 4) would return 11111010₂.

  return byte ^ (create_string_of_1s_at_right(num_bits_to_toggle));
}

void print_bits(uint8_t bits) {
  // Print the bits in 'bits' as '0' and '1' characters.  Do not print a newline
  // at the end.
  //
  // Example:
  // ∙ print_bits_plain(0xff) should output the same as
  //   → printf("11111111").
  // printf("%b", bits);
  printf(PRINTF_BINARY_PATTERN_INT8, PRINTF_BYTE_TO_BINARY_INT8(bits));
}

int main() {

  printf("create_string_of_eight_1s()\n");
  printf("expected: 11111111\nactual:   ");
  print_bits(create_string_of_eight_1s());
  printf("\n");

  printf("create_string_of_1s_at_left(3)\n");
  printf("expected: 11100000\nactual:   ");
  print_bits(create_string_of_1s_at_left(3));
  printf("\n");

  printf("create_string_of_1s_at_right(3)\n");
  printf("expected: 00000111\nactual:   ");
  print_bits(create_string_of_1s_at_right(3));
  printf("\n");

  printf("set_left_bits(00000000₂, 2)\n");
  printf("expected: 11000000\nactual:   ");
  print_bits(set_left_bits(0x00, 2));
  printf("\n");

  printf("set_right_bits(00000000₂, 2)\n");
  printf("expected: 00000011\nactual:   ");
  print_bits(set_right_bits(0x00, 2));
  printf("\n");

  printf("unset_left_bits(11111111₂, 2)\n");
  printf("expected: 00111111\nactual:   ");
  print_bits(unset_left_bits(0xff, 2));
  printf("\n");

  printf("unset_right_bits(11111111₂, 2)\n");
  printf("expected: 11111100\nactual:   ");
  print_bits(unset_right_bits(0xff, 2));
  printf("\n");

  printf("toggle_left_bits(10101010₂, 4)\n");
  printf("expected: 01011010\nactual:   ");
  print_bits(toggle_left_bits(0xaa, 4)); // 0xaa is 10101010₂
  printf("\n");

  printf("toggle_right_bits(10101010₂, 4)\n");
  printf("expected: 10100101\nactual:   ");
  print_bits(toggle_right_bits(0xaa, 4)); // 0xaa is 10101010₂
  printf("\n");

  return EXIT_SUCCESS;
}
#define __WARMUP_C_V2__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
