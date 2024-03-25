#include "s21_math.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// abs tests
START_TEST(s21_abs_test_1) {
  int n = 10;
  ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

START_TEST(s21_abs_test_2) {
  int n = -10;
  ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

START_TEST(s21_abs_test_3) {
  int n = -1234567;
  ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

START_TEST(s21_abs_test_4) {
  int n = 0;
  ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

START_TEST(s21_abs_test_5) {
  int n = -98765;
  ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

// ceil tests
START_TEST(s21_ceil_test_1) {
  long double n = -10.48;
  ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

START_TEST(s21_ceil_test_2) {
  long double n = 0.12;
  ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

START_TEST(s21_ceil_test_3) {
  long double n = -3.14;
  ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

START_TEST(s21_ceil_test_4) {
  long double n = 3.14;
  ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

START_TEST(s21_ceil_test_5) {
  long double n = -1000000;
  ck_assert_ldouble_eq(s21_ceil(n), ceil(n));
}
END_TEST

// fabs tests
START_TEST(s21_fabs_test_1) {
  double n = -10.0;
  ck_assert_ldouble_eq(s21_fabs(n), fabs(n));
}
END_TEST

START_TEST(s21_fabs_test_2) {
  double n = 0.0;
  ck_assert_ldouble_eq(s21_fabs(n), fabs(n));
}
END_TEST

START_TEST(s21_fabs_test_3) {
  double n = -1234.56789;
  ck_assert_ldouble_eq(s21_fabs(n), fabs(n));
}
END_TEST

START_TEST(s21_fabs_test_4) {
  double n = 3.14;
  ck_assert_ldouble_eq(s21_fabs(n), fabs(n));
}
END_TEST

START_TEST(s21_fabs_test_5) {
  double n = -1000000;
  ck_assert_ldouble_eq(s21_fabs(n), fabs(n));
}
END_TEST

// floor tests
START_TEST(s21_floor_test_1) {
  double n = -10.99;
  ck_assert_ldouble_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(s21_floor_test_2) {
  double n = 0.0;
  ck_assert_double_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(s21_floor_test_3) {
  double n = -1234.56789;
  ck_assert_double_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(s21_floor_test_4) {
  double n = 3.14;
  ck_assert_double_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(s21_floor_test_5) {
  double n = -10.10;
  ck_assert_double_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(s21_floor_test_6) {
  double n = 10.10;
  ck_assert_double_eq(s21_floor(n), floor(n));
}
END_TEST

START_TEST(s21_floor_test_7) {
  double n = 0.87;
  ck_assert_double_eq(s21_floor(n), floor(n));
}
END_TEST

// fmod tests
START_TEST(s21_fmod_test_1) {
  double n = 11, t = 4;
  ck_assert_ldouble_eq(s21_fmod(n, t), fmod(n, t));
}
END_TEST

START_TEST(s21_fmod_test_2) {
  double n = 34.34, t = 7;
  ck_assert_ldouble_eq(s21_fmod(n, t), fmod(n, t));
}
END_TEST

START_TEST(s21_fmod_test_3) {
  double n = 34.34, t = 7.5;
  ck_assert_ldouble_eq(s21_fmod(n, t), fmod(n, t));
}
END_TEST

START_TEST(s21_fmod_test_4) {
  double n = -34.34, t = 7.5;
  ck_assert_ldouble_eq(s21_fmod(n, t), fmod(n, t));
}
END_TEST

START_TEST(s21_fmod_test_5) {
  double n = -34.34, t = -7.5;
  ck_assert_ldouble_eq(s21_fmod(n, t), fmod(n, t));
}
END_TEST

START_TEST(s21_fmod_test_6) {
  double n = 34.34, t = -7.5;
  ck_assert_ldouble_eq(s21_fmod(n, t), fmod(n, t));
}
END_TEST

// sqrt tests
START_TEST(s21_sqrt_test_1) {
  double n = 36.36;
  ck_assert_ldouble_eq_tol(s21_sqrt(n), sqrt(n), 0.0000001);
}
END_TEST

START_TEST(s21_sqrt_test_2) {
  double n = 36;
  ck_assert_ldouble_eq_tol(s21_sqrt(n), sqrt(n), 0.0000001);
}
END_TEST

START_TEST(s21_sqrt_test_3) {
  double n = 1.0;
  ck_assert_ldouble_eq_tol(s21_sqrt(n), sqrt(n), 0.0000001);
}
END_TEST

START_TEST(s21_sqrt_test_4) {
  double n = -4;
  ck_assert_ldouble_nan(s21_sqrt(n));
}
END_TEST

START_TEST(s21_sqrt_test_5) {
  double n = 2346236;
  ck_assert_ldouble_eq_tol(s21_sqrt(n), sqrt(n), 0.0000001);
}
END_TEST

START_TEST(s21_sqrt_test_6) {
  double n = 0;
  ck_assert_ldouble_eq_tol(s21_sqrt(n), sqrt(n), 0.0000001);
}
END_TEST

START_TEST(s21_sqrt_test_7) {
  double n = 12.57765;
  ck_assert_ldouble_eq_tol(s21_sqrt(n), sqrt(n), 0.0000001);
}
END_TEST

// acos tests
START_TEST(s21_acos_test_1) {
  double n = 1.0;
  ck_assert_ldouble_eq_tol(s21_acos(n), acos(n), 0.0000001);
}
END_TEST

START_TEST(s21_acos_test_2) {
  double n = -1.0;
  ck_assert_ldouble_eq_tol(s21_acos(n), acos(n), 0.0000001);
}
END_TEST

START_TEST(s21_acos_test_3) {
  double n = 0.314;
  ck_assert_ldouble_eq_tol(s21_acos(n), acos(n), 0.0000001);
}
END_TEST

START_TEST(s21_acos_test_4) {
  double n = -0.314;
  ck_assert_ldouble_eq_tol(s21_acos(n), acos(n), 0.0000001);
}
END_TEST

START_TEST(s21_acos_test_5) {
  double n = 0;
  ck_assert_ldouble_eq_tol(s21_acos(n), acos(n), 0.0000001);
}
END_TEST

START_TEST(s21_acos_test_6) {
  double n = 14;
  ck_assert_ldouble_nan(s21_acos(n));
}
END_TEST

// asin tests
START_TEST(s21_asin_test_1) {
  double n = 1.0;
  ck_assert_ldouble_eq_tol(s21_asin(n), asin(n), 0.0000001);
}
END_TEST

START_TEST(s21_asin_test_2) {
  double n = -1.0;
  ck_assert_ldouble_eq_tol(s21_asin(n), asin(n), 0.0000001);
}
END_TEST

START_TEST(s21_asin_test_3) {
  double n = 0.0;
  ck_assert_ldouble_eq_tol(s21_asin(n), asin(n), 0.0000001);
}
END_TEST

START_TEST(s21_asin_test_4) {
  double n = 0.5;
  ck_assert_ldouble_eq_tol(s21_asin(n), asin(n), 0.0000001);
}
END_TEST

START_TEST(s21_asin_test_5) {
  double n = -0.5;
  ck_assert_ldouble_eq_tol(s21_asin(n), asin(n), 0.0000001);
}
END_TEST

START_TEST(s21_asin_test_6) {
  double n = 14;
  ck_assert_ldouble_nan(s21_asin(n));
}
END_TEST

// atan tests
START_TEST(s21_atan_test_1) {
  double n = 1.0;
  ck_assert_ldouble_eq_tol(s21_atan(n), atan(n), 0.0000001);
}
END_TEST

START_TEST(s21_atan_test_2) {
  double n = -1.0;
  ck_assert_ldouble_eq_tol(s21_atan(n), atan(n), 0.0000001);
}
END_TEST

START_TEST(s21_atan_test_3) {
  double n = 0.0;
  ck_assert_ldouble_eq_tol(s21_atan(n), atan(n), 0.0000001);
}
END_TEST

START_TEST(s21_atan_test_4) {
  double n = -3.14;
  ck_assert_ldouble_eq_tol(s21_atan(n), atan(n), 0.0000001);
}
END_TEST

START_TEST(s21_atan_test_5) {
  double n = 3.14;
  ck_assert_ldouble_eq_tol(s21_atan(n), atan(n), 0.0000001);
}
END_TEST

START_TEST(s21_atan_test_6) {
  double n = 23.43;
  ck_assert_ldouble_eq_tol(s21_atan(n), atan(n), 0.0000001);
}
END_TEST

// cos test
START_TEST(s21_cos_test_1) {
  double n = 3;
  ck_assert_ldouble_eq_tol(s21_cos(n), cos(n), 0.0000001);
}
END_TEST

START_TEST(s21_cos_test_2) {
  double n = 3.14;
  ck_assert_ldouble_eq_tol(s21_cos(n), cos(n), 0.0000001);
}
END_TEST

START_TEST(s21_cos_test_3) {
  double n = 0.0;
  ck_assert_ldouble_eq_tol(s21_cos(n), cos(n), 0.0000001);
}
END_TEST

START_TEST(s21_cos_test_4) {
  double n = -3.14;
  ck_assert_ldouble_eq_tol(s21_cos(n), cos(n), 0.0000001);
}
END_TEST

// tan test
START_TEST(s21_tan_test_1) {
  double n = 3;
  ck_assert_ldouble_eq_tol(s21_tan(n), tan(n), 0.0000001);
}
END_TEST

START_TEST(s21_tan_test_2) {
  double n = 3.14;
  ck_assert_ldouble_eq_tol(s21_tan(n), tan(n), 0.0000001);
}
END_TEST

START_TEST(s21_tan_test_3) {
  double n = 0.0;
  ck_assert_ldouble_eq_tol(s21_tan(n), tan(n), 0.0000001);
}
END_TEST

START_TEST(s21_tan_test_4) {
  double n = -3.14;
  ck_assert_ldouble_eq_tol(s21_tan(n), tan(n), 0.0000001);
}
END_TEST

// exp tests
START_TEST(s21_exp_test_1) {
  double n = 3;
  ck_assert_ldouble_eq_tol(s21_exp(n), exp(n), 0.0000001);
}
END_TEST

START_TEST(s21_exp_test_2) {
  double n = 3.14;
  ck_assert_ldouble_eq_tol(s21_exp(n), exp(n), 0.0000001);
}
END_TEST

START_TEST(s21_exp_test_3) {
  double n = 0.0;
  ck_assert_ldouble_eq_tol(s21_exp(n), exp(n), 0.0000001);
}
END_TEST

START_TEST(s21_exp_test_4) {
  double n = -3.14;
  ck_assert_ldouble_eq_tol(s21_exp(n), exp(n), 0.0000001);
}
END_TEST

// log tests
START_TEST(s21_log_test_1) {
  double n = 3;
  ck_assert_ldouble_eq_tol(s21_log(n), log(n), 0.0000001);
}
END_TEST

START_TEST(s21_log_test_2) {
  double n = 3.14;
  ck_assert_ldouble_eq_tol(s21_log(n), log(n), 0.0000001);
}
END_TEST

START_TEST(s21_log_test_3) {
  double n = 0.0;
  ck_assert_ldouble_infinite(s21_log(n));
}
END_TEST

START_TEST(s21_log_test_4) {
  double n = -1;
  ck_assert_ldouble_nan(s21_log(n));
}
END_TEST

START_TEST(s21_log_test_5) {
  double n = 1;
  ck_assert_ldouble_eq_tol(s21_log(n), log(n), 0.0000001);
}
END_TEST

START_TEST(s21_log_test_6) {
  double n = 99999;
  ck_assert_ldouble_eq_tol(s21_log(n), log(n), 0.0000001);
}
END_TEST

// sin test
START_TEST(s21_sin_test_1) {
  double n = 3;
  ck_assert_ldouble_eq_tol(s21_sin(n), sin(n), 0.0000001);
}
END_TEST

START_TEST(s21_sin_test_2) {
  double n = 3.14;
  ck_assert_ldouble_eq_tol(s21_sin(n), sin(n), 0.0000001);
}
END_TEST

START_TEST(s21_sin_test_3) {
  double n = 0.0;
  ck_assert_ldouble_eq_tol(s21_sin(n), sin(n), 0.0000001);
}
END_TEST

START_TEST(s21_sin_test_4) {
  double n = -3.14;
  ck_assert_ldouble_eq_tol(s21_sin(n), sin(n), 0.0000001);
}
END_TEST

// pow tests
START_TEST(s21_pow_test_1) {
  double n = 2, t = 10;
  ck_assert_ldouble_eq_tol(s21_pow(n, t), pow(n, t), 0.0000001);
}
END_TEST

START_TEST(s21_pow_test_2) {
  double n = -3.14, t = 7;
  ck_assert_ldouble_eq_tol(s21_pow(n, t), pow(n, t), 0.0000001);
}
END_TEST

START_TEST(s21_pow_test_3) {
  double n = 0.0, t = 0.0;
  ck_assert_ldouble_eq_tol(s21_pow(n, t), pow(n, t), 0.0000001);
}
END_TEST

START_TEST(s21_pow_test_4) {
  double n = -3, t = -3;
  ck_assert_ldouble_eq_tol(s21_pow(n, t), pow(n, t), 0.0000001);
}
END_TEST

START_TEST(s21_pow_test_5) {
  double n = 4.0, t = -2.0;
  ck_assert_ldouble_eq_tol(s21_pow(n, t), pow(n, t), 0.0000001);
}
END_TEST

START_TEST(s21_pow_test_6) {
  double n = 4.15, t = -2.35;
  ck_assert_ldouble_eq_tol(s21_pow(n, t), pow(n, t), 0.0000001);
}
END_TEST

Suite *s21_abs_suite(void) {
  TCase *tc = tcase_create("s21_abs_core");
  Suite *s = suite_create("s21_abs_tests");

  tcase_add_test(tc, s21_abs_test_1);
  tcase_add_test(tc, s21_abs_test_2);
  tcase_add_test(tc, s21_abs_test_3);
  tcase_add_test(tc, s21_abs_test_4);
  tcase_add_test(tc, s21_abs_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_ceil_suite(void) {
  TCase *tc = tcase_create("s21_ceil_core");
  Suite *s = suite_create("s21_ceil_tests");

  tcase_add_test(tc, s21_ceil_test_1);
  tcase_add_test(tc, s21_ceil_test_2);
  tcase_add_test(tc, s21_ceil_test_3);
  tcase_add_test(tc, s21_ceil_test_4);
  tcase_add_test(tc, s21_ceil_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_fabs_suite(void) {
  TCase *tc = tcase_create("s21_fabs_core");
  Suite *s = suite_create("s21_fabs_tests");

  tcase_add_test(tc, s21_fabs_test_1);
  tcase_add_test(tc, s21_fabs_test_2);
  tcase_add_test(tc, s21_fabs_test_3);
  tcase_add_test(tc, s21_fabs_test_4);
  tcase_add_test(tc, s21_fabs_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_floor_suite(void) {
  TCase *tc = tcase_create("s21_floor_core");
  Suite *s = suite_create("s21_floor_tests");

  tcase_add_test(tc, s21_floor_test_1);
  tcase_add_test(tc, s21_floor_test_2);
  tcase_add_test(tc, s21_floor_test_3);
  tcase_add_test(tc, s21_floor_test_4);
  tcase_add_test(tc, s21_floor_test_5);
  tcase_add_test(tc, s21_floor_test_6);
  tcase_add_test(tc, s21_floor_test_7);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_fmod_suite(void) {
  TCase *tc = tcase_create("s21_fmod_core");
  Suite *s = suite_create("s21_fmod_tests");

  tcase_add_test(tc, s21_fmod_test_1);
  tcase_add_test(tc, s21_fmod_test_2);
  tcase_add_test(tc, s21_fmod_test_3);
  tcase_add_test(tc, s21_fmod_test_4);
  tcase_add_test(tc, s21_fmod_test_5);
  tcase_add_test(tc, s21_fmod_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sqrt_suite(void) {
  TCase *tc = tcase_create("s21_sqrt_core");
  Suite *s = suite_create("s21_sqrt_tests");

  tcase_add_test(tc, s21_sqrt_test_1);
  tcase_add_test(tc, s21_sqrt_test_2);
  tcase_add_test(tc, s21_sqrt_test_3);
  tcase_add_test(tc, s21_sqrt_test_4);
  tcase_add_test(tc, s21_sqrt_test_5);
  tcase_add_test(tc, s21_sqrt_test_6);
  tcase_add_test(tc, s21_sqrt_test_7);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_acos_suite(void) {
  TCase *tc = tcase_create("s21_acos_core");
  Suite *s = suite_create("s21_acos_tests");

  tcase_add_test(tc, s21_acos_test_1);
  tcase_add_test(tc, s21_acos_test_2);
  tcase_add_test(tc, s21_acos_test_3);
  tcase_add_test(tc, s21_acos_test_4);
  tcase_add_test(tc, s21_acos_test_5);
  tcase_add_test(tc, s21_acos_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_asin_suite(void) {
  TCase *tc = tcase_create("s21_asin_core");
  Suite *s = suite_create("s21_asin_tests");

  tcase_add_test(tc, s21_asin_test_1);
  tcase_add_test(tc, s21_asin_test_2);
  tcase_add_test(tc, s21_asin_test_3);
  tcase_add_test(tc, s21_asin_test_4);
  tcase_add_test(tc, s21_asin_test_5);
  tcase_add_test(tc, s21_asin_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_atan_suite(void) {
  TCase *tc = tcase_create("s21_atan_core");
  Suite *s = suite_create("s21_atan_tests");

  tcase_add_test(tc, s21_atan_test_1);
  tcase_add_test(tc, s21_atan_test_2);
  tcase_add_test(tc, s21_atan_test_3);
  tcase_add_test(tc, s21_atan_test_4);
  tcase_add_test(tc, s21_atan_test_5);
  tcase_add_test(tc, s21_atan_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_cos_suite(void) {
  TCase *tc = tcase_create("s21_cos_core");
  Suite *s = suite_create("s21_cos_tests");

  tcase_add_test(tc, s21_cos_test_1);
  tcase_add_test(tc, s21_cos_test_2);
  tcase_add_test(tc, s21_cos_test_3);
  tcase_add_test(tc, s21_cos_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_exp_suite(void) {
  TCase *tc = tcase_create("s21_exp_core");
  Suite *s = suite_create("s21_exp_tests");

  tcase_add_test(tc, s21_exp_test_1);
  tcase_add_test(tc, s21_exp_test_2);
  tcase_add_test(tc, s21_exp_test_3);
  tcase_add_test(tc, s21_exp_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_log_suite(void) {
  TCase *tc = tcase_create("s21_log_core");
  Suite *s = suite_create("s21_log_tests");

  tcase_add_test(tc, s21_log_test_1);
  tcase_add_test(tc, s21_log_test_2);
  tcase_add_test(tc, s21_log_test_3);
  tcase_add_test(tc, s21_log_test_4);
  tcase_add_test(tc, s21_log_test_5);
  tcase_add_test(tc, s21_log_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_pow_suite(void) {
  TCase *tc = tcase_create("s21_pow_core");
  Suite *s = suite_create("s21_pow_tests");

  tcase_add_test(tc, s21_pow_test_1);
  tcase_add_test(tc, s21_pow_test_2);
  tcase_add_test(tc, s21_pow_test_3);
  tcase_add_test(tc, s21_pow_test_4);
  tcase_add_test(tc, s21_pow_test_5);
  tcase_add_test(tc, s21_pow_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sin_suite(void) {
  TCase *tc = tcase_create("s21_sin_core");
  Suite *s = suite_create("s21_sin_tests");

  tcase_add_test(tc, s21_sin_test_1);
  tcase_add_test(tc, s21_sin_test_2);
  tcase_add_test(tc, s21_sin_test_3);
  tcase_add_test(tc, s21_sin_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_tan_suite(void) {
  TCase *tc = tcase_create("s21_tan_core");
  Suite *s = suite_create("s21_tan_tests");

  tcase_add_test(tc, s21_tan_test_1);
  tcase_add_test(tc, s21_tan_test_2);
  tcase_add_test(tc, s21_tan_test_3);
  tcase_add_test(tc, s21_tan_test_4);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr;

  sr = srunner_create(s21_abs_suite());
  srunner_add_suite(sr, s21_ceil_suite());
  srunner_add_suite(sr, s21_fabs_suite());
  srunner_add_suite(sr, s21_floor_suite());
  srunner_add_suite(sr, s21_fmod_suite());
  srunner_add_suite(sr, s21_acos_suite());
  srunner_add_suite(sr, s21_asin_suite());
  srunner_add_suite(sr, s21_atan_suite());
  srunner_add_suite(sr, s21_cos_suite());
  srunner_add_suite(sr, s21_exp_suite());
  srunner_add_suite(sr, s21_log_suite());
  srunner_add_suite(sr, s21_pow_suite());
  srunner_add_suite(sr, s21_sin_suite());
  srunner_add_suite(sr, s21_sqrt_suite());
  srunner_add_suite(sr, s21_tan_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}
