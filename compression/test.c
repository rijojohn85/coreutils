#include "compress.h"
#include "munit/munit.h"
#include <stdio.h>
#include <stdlib.h>

// int munit_suite_main(const MunitSuite *suite, void *user_data, int argc,
//                      char *const *argv);
MunitResult file_open_test(const MunitParameter params[],
                           void *user_data_or_fixture);

MunitResult file_open_failure_test(const MunitParameter params[],
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
