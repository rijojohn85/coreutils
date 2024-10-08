
#include "../munit/munit.h"
#include "bit_writer.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

MunitResult biteWriter_open_test(const MunitParameter params[],
                                 void *user_data_or_fixture);
MunitResult bitwriter_write_bit_full(const MunitParameter params[],
                                     void *user_data_or_fixture);
MunitTest tests[] = {
    {
        "/biteWriter_open_test",      // name of test
        biteWriter_open_test,         // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    /* new tests come below here */

    {
        "/bitwriter_write_bit_full",  // name of test
        bitwriter_write_bit_full,     // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite suite = {
    "/bit-writer-tests", /* name of the test suit */
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  return munit_suite_main(&suite, NULL, argc, argv);
}
MunitResult biteWriter_open_test(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  struct BitWriter a_writer = open_bit_writer("test.huffman");
  munit_assert_ptr_not_null(a_writer.file);
  // munit_assert_uint32(a_writer.current_byte, =, 0x0000);
  munit_assert_uint8(32, =, a_writer.num_bits_left);
  fclose(a_writer.file);
  return MUNIT_OK;
}

MunitResult bitwriter_write_bit_full(const MunitParameter params[],
                                     void *user_data_or_fixture) {

  (void)params;
  (void)user_data_or_fixture;
  struct BitWriter a_writer = open_bit_writer("test.huffman");
  write_bits(&a_writer, 0x000f, 8);
  // printf("\nbits: %d:%d\n", a_writer.current_byte, a_writer.num_bits_left);
  munit_assert_uint32(0x000f, =, a_writer.current_byte);
  munit_assert_uint8(24, =, a_writer.num_bits_left);
  write_bits(&a_writer, 0x0003, 2);
  munit_assert_uint32(0x003f, =, a_writer.current_byte);
  munit_assert_uint8(22, =, a_writer.num_bits_left);
  fclose(a_writer.file);
  return MUNIT_OK;
}
