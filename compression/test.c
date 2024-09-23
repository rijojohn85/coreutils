#include "compress.h"
#include "hashmap.c/hashmap.h"
#include "munit/munit.h"
#include <stdio.h>
#include <stdlib.h>

// int munit_suite_main(const MunitSuite *suite, void *user_data, int argc,
//                      char *const *argv);
MunitResult file_open_test(const MunitParameter params[],
                           void *user_data_or_fixture);

MunitResult file_open_failure_test(const MunitParameter params[],
                                   void *user_data_or_fixture);
MunitResult test_insert_into_map(const MunitParameter params[],
                                 void *user_data_or_fixture);
MunitResult test_get_wrong_data(const MunitParameter params[],
                                void *user_data_or_fixture);
MunitResult test_count_of_char(const MunitParameter params[],
                               void *user_data_or_fixture);
MunitResult test_with_file(const MunitParameter params[],
                           void *user_data_or_fixture);
MunitTest tests[] = {
    {
        "/file_open_test",            // name of test
        file_open_test,               // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    /* new tests come below here */

    {
        "/file_open_failure_test",    // name of test
        file_open_failure_test,       // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {
        "/test_insert_into_map",      // name of test
        test_insert_into_map,         // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {
        "/test_get_wrong_data",       // name of test
        test_get_wrong_data,          // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {
        "/test_count_of_char",        // name of test
        test_count_of_char,           // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {
        "/test_with_file",            // name of test
        test_with_file,               // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite suite = {
    "/compression-tests", /* name of the test suit */
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
MunitResult file_open_test(const MunitParameter params[],
                           void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  FILE *fp = open_file("file.txt");
  munit_assert_not_null(fp);
  fclose(fp);
  return MUNIT_OK;
}
MunitResult file_open_failure_test(const MunitParameter params[],
                                   void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  FILE *fp = open_file("test.txt");
  munit_assert_null(fp);
  return MUNIT_OK;
}

MunitResult test_insert_into_map(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  struct hashmap *map = hashmap_new(sizeof(struct letter_count), 0, 0, 0,
                                    letter_hash, letter_compare, NULL, NULL);
  insert_into_map('x', map);
  struct letter_count *letter;
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'x'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'x');
  munit_assert_int(letter->count, ==, 1);
  hashmap_free(map);
  return MUNIT_OK;
}

MunitResult test_get_wrong_data(const MunitParameter params[],
                                void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  struct hashmap *map = hashmap_new(sizeof(struct letter_count), 0, 0, 0,
                                    letter_hash, letter_compare, NULL, NULL);
  insert_into_map('x', map);
  struct letter_count *letter;
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'r'});
  munit_assert_null(letter);
  hashmap_free(map);
  return MUNIT_OK;
}

MunitResult test_count_of_char(const MunitParameter params[],
                               void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  struct hashmap *map = hashmap_new(sizeof(struct letter_count), 0, 0, 0,
                                    letter_hash, letter_compare, NULL, NULL);
  insert_into_map('x', map);
  insert_into_map('r', map);
  insert_into_map('x', map);
  insert_into_map('x', map);
  struct letter_count *letter;
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'x'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'x');
  munit_assert_int(letter->count, ==, 3);
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'r'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'r');
  munit_assert_int(letter->count, ==, 1);
  hashmap_free(map);
  return MUNIT_OK;
}
MunitResult test_with_file(const MunitParameter params[],
                           void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  char *file_name = "file.txt";
  FILE *fp = open_file(file_name);
  struct hashmap *map = get_char_count(fp);

  struct letter_count *letter;
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'a'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'a');
  munit_assert_int(letter->count, ==, 1);
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'b'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'b');
  munit_assert_int(letter->count, ==, 2);
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'c'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'c');
  munit_assert_int(letter->count, ==, 3);
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'd'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'd');
  munit_assert_int(letter->count, ==, 4);
  letter =
      (struct letter_count *)hashmap_get(map, &(struct letter_count){.c = 'e'});
  munit_assert_not_null(letter);
  munit_assert_char(letter->c, ==, 'e');
  munit_assert_int(letter->count, ==, 5);
  fclose(fp);
  return MUNIT_OK;
}
