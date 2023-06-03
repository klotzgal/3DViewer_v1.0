#include <check.h>

#include "../libs/lib.h"

START_TEST(test_1) {
  parser();
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");
  TCase *tc_test_1;
  tc_test_1 = tcase_create("test_1");
  suite_add_tcase(s, tc_test_1);
  tcase_add_test(tc_test_1, test_1);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}
