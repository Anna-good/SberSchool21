#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

// is_equal tests
START_TEST(s21_is_equal_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 123;
  val2.bits[0] = 123;

  ck_assert_uint_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_equal_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 123;
  val1.bits[3] = 0b00000000000001110000000000000000;
  val2.bits[0] = 123;
  val2.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_uint_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 123;
  val1.bits[3] = 0b00000000000000000000000000000000;
  val2.bits[0] = 123;
  val2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_4) {
  s21_decimal val1;
  s21_decimal val2;
  val1.bits[0] = 0b01011000101000100100010110000000;
  val1.bits[1] = 0b00100000100000100000010110000000;
  val1.bits[2] = 0b10101011000011000000110000000000;
  val1.bits[3] = 0b00000000000111000000000000000000;

  val2.bits[0] = 0b01011000101000100100010110000000;
  val2.bits[1] = 0b00100000100000100000010110000000;
  val2.bits[2] = 0b10101011000011000000110000000000;
  val2.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_uint_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

// is_not_equal tests
START_TEST(s21_is_not_equal_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 0b11111111111111111111111111111111;
  val1.bits[3] = 0b00000000000001110000000000000000;
  val2.bits[0] = 0b11111111111111111111111111111111;
  val2.bits[3] = 0b00000000000001110000000000000000;

  ck_assert_uint_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 0b11111111111111111111111111111111;
  val1.bits[3] = 0b00000000000001110000000000000000;
  val2.bits[2] = 0b11111111111111111111111111111111;
  val2.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_uint_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 0b00000000000100001000000101000000;
  val1.bits[3] = 0b10000000000000000000000000000000;
  val2.bits[0] = 0b00000000000100001000000101000000;
  val2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_not_equal(val1, val2), 0);
}
END_TEST

// is_greater tests
START_TEST(s21_is_greater_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 123;
  val1.bits[3] = 0b00000000000001110000000000000000;
  val2.bits[2] = 123;
  val2.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_uint_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(s21_is_greater_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 123;
  val1.bits[3] = 0b00000000000000000000000000000000;
  val2.bits[2] = 123;
  val2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_greater_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 123;
  val2.bits[2] = 123;

  ck_assert_uint_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(s21_is_greater_test_4) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 123;
  val1.bits[3] = 0b10000000000000000000000000000000;
  val2.bits[2] = 123;
  val2.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(s21_is_greater_test_5) {
  s21_decimal val1;
  s21_decimal val2;
  val1.bits[0] = 0b11111111111111111111111111111111;
  val1.bits[1] = 0b11111111111111111111111111111111;
  val1.bits[2] = 0b11111111111111111111111111111111;
  val1.bits[3] = 0b00000000000111000000000000000000;

  val2.bits[0] = 0b11111111111111111111111111111111;
  val2.bits[1] = 0b11111111111111111111111111111111;
  val2.bits[2] = 0b01111111111111111111111111111111;
  val2.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_uint_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_greater_test_6) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 12;
  val1.bits[3] = 0b10000000000000000000000000000000;
  val2.bits[2] = 123;
  val2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_greater_test_7) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 124;
  val1.bits[3] = 0b10000000000000000000000000000000;
  val2.bits[2] = 1;
  val2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

// is greaterr or equal tests
START_TEST(s21_is_greater_or_equal_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[1] = 123;
  val2.bits[1] = 123;

  ck_assert_uint_eq(s21_is_greater_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 1234;
  val2.bits[2] = 123;
  val2.bits[3] = 0b00000000000001000000000000000000;

  ck_assert_uint_eq(s21_is_greater_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[2] = 1234;
  val1.bits[3] = 0b00000000000010000000000000000000;
  val2.bits[2] = 123;

  ck_assert_uint_eq(s21_is_greater_or_equal(val1, val2), 0);
}
END_TEST

// is less tests
START_TEST(s21_is_less_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 0b01011000101000100100010110000000;
  val1.bits[1] = 0b00100000100000100000010110000000;
  val1.bits[2] = 0b00000001000011000000110000000000;
  val1.bits[3] = 0b00000000000111000000000000000000;

  val2.bits[0] = 0b01011000101000100100010110000000;
  val2.bits[1] = 0b00100000100000100000010110000000;
  val2.bits[2] = 0b10101011000011000000110000000000;
  val2.bits[3] = 0b00000000000111000000000000000000;

  ck_assert_uint_eq(s21_is_less(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_less_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 0b01011000101000100100010110000000;
  val1.bits[3] = 0b10000000000000000000000000000000;
  val2.bits[0] = 0b01011000101000100100010110000000;
  val2.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_less(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_less_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 12345;
  val2.bits[0] = 1234;

  ck_assert_uint_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(s21_is_less_test_4) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 1234;
  val2.bits[0] = 1234;

  ck_assert_uint_eq(s21_is_less(val1, val2), 0);
}
END_TEST

// is less or equal tests
START_TEST(s21_is_less_or_equal_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 1234;
  val2.bits[0] = 1234;

  ck_assert_uint_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 124;
  val1.bits[3] = 0b10000000000000000000000000000000;
  val2.bits[0] = 1;
  val2.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_uint_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 124;
  val2.bits[0] = 1;

  ck_assert_uint_eq(s21_is_less_or_equal(val1, val2), 0);
}
END_TEST

// truncate tests
START_TEST(s21_truncate_test_1) {
  s21_decimal value = {{0}};
  s21_decimal result;
  value.bits[0] = 123456;
  value.bits[3] = 0b00000000000000010000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 12345);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal value = {{0}};
  s21_decimal result;
  value.bits[0] = 123456;
  value.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal value = {{0}};
  s21_decimal result;
  value.bits[0] = 0b01101011000000110000100000000000;
  value.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b110110110010100100000);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_4) {
  s21_decimal value = {{0}};
  s21_decimal result;
  value.bits[0] = 0b01101011000000110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[3] = 0b00000000000001110000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b11110001010001100010100110001100);
  ck_assert_uint_eq(result.bits[1], 0b00000000000000000000000010110011);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_5) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b01101011001100110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[2] = 0b11101011010000010000101100000000;
  value.bits[3] = 0b00000000000011110000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b11010111101100101001011100110010);
  ck_assert_uint_eq(result.bits[1], 0b100001000110111);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_6) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b01101011001100110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[2] = 0b11101011010000010000101100000000;
  value.bits[3] = 0b00000000000011110000000000011000;

  ck_assert_int_eq(s21_truncate(value, &result), 1);

  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_7) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b01101011001100110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[2] = 0b11101011010000010000101100000000;
  value.bits[3] = 0b00000000001111110000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 1);

  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_8) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b01101011001100110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[2] = 0b11101011010000010000101100001110;
  value.bits[3] = 0b10000000000010100000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b11100101010001101110010011010101);
  ck_assert_uint_eq(result.bits[1], 0b1100101000010100111010110000110);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_truncate_test_9) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b11111111111111111111111111111111);
  ck_assert_uint_eq(result.bits[1], 0b11111111111111111111111111111111);
  ck_assert_uint_eq(result.bits[2], 0b11111111111111111111111111111111);
  ck_assert_uint_eq(result.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_truncate_test_10) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b00000000000111000000000000000000;

  ck_assert_int_eq(s21_truncate(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b00000000000000000000000000000111);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

// floor tests
START_TEST(s21_floor_test_1) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b01101011001100110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[2] = 0b11101011010000010000101100000000;
  value.bits[3] = 0b00000000000011110000000000000000;

  ck_assert_int_eq(s21_floor(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b11010111101100101001011100110010);
  ck_assert_uint_eq(result.bits[1], 0b100001000110111);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_floor_test_2) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b01101011001100110000100000000000;
  value.bits[1] = 0b01101011010000010000101100000000;
  value.bits[2] = 0b11101011010000010000101100000000;
  value.bits[3] = 0b10000000000000110000000000000000;

  ck_assert_int_eq(s21_floor(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b11100111100001111111110010101111);
  ck_assert_uint_eq(result.bits[1], 0b01101010100110100110111011011011);
  ck_assert_uint_eq(result.bits[2], 0b1111000011100110011100);
  ck_assert_uint_eq(result.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

// round tests
START_TEST(s21_round_test_1) {
  s21_decimal value;
  s21_decimal result;
  value.bits[0] = 0b00010000010000111000001010100000;
  value.bits[1] = 0b00011001010001101010001001001000;
  value.bits[2] = 0b00000100000000001100100111110010;
  value.bits[3] = 0b00000000000011110000000000000000;

  ck_assert_int_eq(s21_round(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 0b01110011110100011010011100010010);
  ck_assert_uint_eq(result.bits[1], 0b100100000);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal value = {{0}};
  s21_decimal result;
  value.bits[0] = 12344;
  value.bits[3] = 0b00000000000000010000000000000000;

  ck_assert_int_eq(s21_round(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 1234);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal value = {{0}};
  s21_decimal result;
  value.bits[0] = 12344;
  value.bits[3] = 0b10000000000000010000000000000000;

  ck_assert_int_eq(s21_round(value, &result), 0);

  ck_assert_uint_eq(result.bits[0], 1234);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

// from_decimal_to_float
START_TEST(s21_from_decimal_to_float_test_1) {
  s21_decimal val = {{0}};
  float res;
  val.bits[0] = 1234567890;
  val.bits[3] = 0b00000000000001110000000000000000;

  ck_assert_int_eq(s21_from_decimal_to_float(val, &res), 0);
  ck_assert_float_eq(res, 123.4567890);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_2) {
  s21_decimal val = {{0}};
  float res;
  val.bits[0] = 12345;
  val.bits[3] = 0b00000000000000010000000000000000;

  ck_assert_int_eq(s21_from_decimal_to_float(val, &res), 0);
  ck_assert_float_eq(res, 1234.5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_3) {
  s21_decimal val = {{0}};
  float res;
  val.bits[0] = 12345;
  val.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_int_eq(s21_from_decimal_to_float(val, &res), 0);
  ck_assert_float_eq(res, 12345);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_4) {
  s21_decimal val = {{0}};
  float res;
  val.bits[0] = 12345;
  val.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_int_eq(s21_from_decimal_to_float(val, &res), 0);
  ck_assert_float_eq(res, -12345);
}
END_TEST

// int to decimal tests
START_TEST(s21_from_int_to_decimal_test_1) {
  s21_decimal res;
  int a = -1234;
  int r = s21_from_int_to_decimal(a, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], (unsigned)1234);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (unsigned)2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  s21_decimal res;
  int a = S21_INT_MAX;
  int r = s21_from_int_to_decimal(a, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], (unsigned)2147483647);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_3) {
  s21_decimal res;
  int a = S21_INT_MIN;
  int r = s21_from_int_to_decimal(a, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], (unsigned)2147483648);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (unsigned)2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
  s21_decimal res;
  int a = 0;
  int r = s21_from_int_to_decimal(a, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], (unsigned)0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

// decimal to int tests
START_TEST(s21_from_decimal_to_int_test_1) {
  s21_decimal src = {{2147483648}};
  int a;
  int r = s21_from_decimal_to_int(src, &a);
  ck_assert_int_eq(r, 1);
  ck_assert_int_eq(0, a);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  s21_decimal src = {{2147483648, 0, 0, 2147483648}};
  int a;
  int r = s21_from_decimal_to_int(src, &a);
  ck_assert_int_eq(r, 0);
  ck_assert_int_eq(-2147483648, a);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  s21_decimal src = {{2147483647}};
  int a;
  int r = s21_from_decimal_to_int(src, &a);
  ck_assert_int_eq(r, 0);
  ck_assert_int_eq(2147483647, a);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  s21_decimal src = {{2147483649}};
  int a;
  int r = s21_from_decimal_to_int(src, &a);
  ck_assert_int_eq(r, 1);
  ck_assert_int_eq(0, a);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_5) {
  s21_decimal src = {{5231432, 0, 0, 2147483648}};
  int a;
  int r = s21_from_decimal_to_int(src, &a);
  ck_assert_int_eq(r, 0);
  ck_assert_int_eq(-5231432, a);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_6) {
  s21_decimal src = {{5231432, 1, 0, 2147483648}};
  int a;
  int r = s21_from_decimal_to_int(src, &a);
  ck_assert_int_eq(r, 1);
  ck_assert_int_eq(0, a);
}
END_TEST

// div tests
START_TEST(s21_div_test_1) {
  s21_decimal v1 = {{35}};
  s21_decimal v2 = {{8}};
  s21_decimal res;
  s21_decimal check = {{4375}};
  check.bits[3] = 3 << 16;
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_2) {
  s21_decimal v1 = {{160}};
  s21_decimal v2 = {{10}};
  s21_decimal res;
  s21_decimal check = {{16}};
  check.bits[3] = 0;
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_3) {
  s21_decimal v1 = {{160}};
  s21_decimal v2 = {{0}};
  s21_decimal res;
  s21_decimal check = {{0}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 3);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_4) {
  s21_decimal v1 = {{35210}};
  s21_decimal v2 = {{3521}};
  s21_decimal res;
  s21_decimal check = {{10}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_5) {
  s21_decimal v1 = {{1, 0, 0, 2147483648}};
  s21_decimal v2 = {{0b01000000000000000000000000000000,
                     0b01000110011101001110110111101010,
                     0b10011111001011001001110011010000}};
  s21_decimal res;
  s21_decimal check = {{0}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 2);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_6) {
  s21_decimal v1 = {{1}};
  s21_decimal v2 = {{1}};
  v2.bits[3] = 28 << 16;
  s21_decimal res;
  s21_decimal check = {{0b00010000000000000000000000000000,
                        0b00111110001001010000001001100001,
                        0b00100000010011111100111001011110, 0}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_7) {
  s21_decimal v1 = {{1, 10235, 0, 2147745796}};
  s21_decimal v2 = {{2, 0, 0, 2147483648}};
  s21_decimal res;
  s21_decimal check = {
      {0b00000000000000000000000000000101, 0b1100011111100111, 0, 327680}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_8) {
  s21_decimal v1 = {{1, 103, 2, 2147942400}};
  s21_decimal v2 = {{0b00000000000000000000000000000101,
                     0b00000000000000000000001000000011, 0b1010, 65536}};
  s21_decimal res;
  s21_decimal check = {{2, 0, 0, 2147942400}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_9) {
  s21_decimal v1 = {{1}};
  s21_decimal v2 = {{3, 0, 0, 2147483648}};
  s21_decimal res;
  s21_decimal check = {{0b00000101010101010101010101010101,
                        0b00010100101101110000000011001011,
                        0b00001010110001010100010011001010, 2149318656}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

// float to decimal
START_TEST(s21_from_float_to_decimal_test_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  float k = -14.00000000000000001f;
  val2.bits[0] = 14;
  val2.bits[3] = 0b10000000000000000000000000000000;
  s21_from_float_to_decimal(k, &val1);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  float k = -146.1858f;
  val2.bits[0] = 1461858063;
  val2.bits[3] = 0b10000000000001110000000000000000;
  s21_from_float_to_decimal(k, &val1);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  float k = 912324.185843f;
  val2.bits[0] = 0b00011111110010011001111110010011;
  val2.bits[3] = 0b00000000000001000000000000000000;
  s21_from_float_to_decimal(k, &val1);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_4) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  float k = -1.00000000001f;
  val2.bits[0] = 1;
  val2.bits[3] = 0b10000000000000000000000000000000;
  s21_from_float_to_decimal(k, &val1);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_5) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  float k = -0.00000000000000002342351f;
  val2.bits[0] = 0;
  val2.bits[3] = 0b10000000000000000000000000000000;
  s21_from_float_to_decimal(k, &val1);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_6) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  float k = 0.000000000000000000000000123f;
  val2.bits[0] = 0;
  val2.bits[3] = 0b00000000000000000000000000000000;
  s21_from_float_to_decimal(k, &val1);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

// add tests
START_TEST(s21_add_test_1) {
  s21_decimal v1 = {{0}};
  s21_decimal v2 = {{0}};
  s21_decimal res;
  int r = s21_add(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_2) {
  s21_decimal v1 = {{12345, 0, 0, 196608}};
  s21_decimal v2 = {{12345, 0, 0, 65536}};
  s21_decimal res;
  int r = s21_add(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], 1246845);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 196608);
}

START_TEST(s21_add_test_3) {
  s21_decimal v1 = {{1, 0, 0, 2147483648}};
  s21_decimal v2 = {{1, 0, 0, 0}};
  s21_decimal res;
  int r = s21_add(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_4) {
  s21_decimal v1 = {{0, 1, 0, 2147483648}};
  s21_decimal v2 = {{0, 1, 0, 2147483648}};
  s21_decimal res;
  int r = s21_add(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 2);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_add_test_5) {
  s21_decimal var1 = {{50, 0, 0, 0}};
  s21_decimal var2 = {{777, 3, 0, 0}};
  var2.bits[3] = 3 << 16;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{50777, 3, 0, 0}};
  ch.bits[3] = 3 << 16;
  int ret = s21_add(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_add_test_6) {
  s21_decimal var1 = {{8666, 5, 0, 0}};
  var1.bits[3] = 5 << 16;
  s21_decimal var2 = {{777, 3, 0, 0}};
  var2.bits[3] = 10 << 16;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{866600777, 500003, 0, 0}};
  ch.bits[3] = 10 << 16;
  int ret = s21_add(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_add_test_7) {
  s21_decimal var1 = {{50, 0, 0, 0}};
  var1.bits[3] = 1 << 31;
  s21_decimal var2 = {{777, 3, 0, 0}};
  var2.bits[3] = 3 << 16;
  var2.bits[3] |= (1 << 31);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{50777, 3, 0, 0}};
  ch.bits[3] = 3 << 16;
  ch.bits[3] |= (1 << 31);
  int ret = s21_add(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_add_test_8) {
  s21_decimal var1 = {{50, 60, 0, 0}};
  var1.bits[3] = 1 << 31;
  var1.bits[3] |= 3 << 16;
  s21_decimal var2 = {{4, 5555, 333, 0}};
  var2.bits[3] = 7 << 16;
  var2.bits[3] |= (1 << 31);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{500004, 605555, 333, 0}};
  ch.bits[3] = 7 << 16;
  ch.bits[3] |= (1 << 31);
  int ret = s21_add(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_add_test_9) {
  s21_decimal var1 = {{50, 50, 0, 0}};
  s21_decimal var2 = {{50, 0, 0, 0}};
  var2.bits[3] = 1 << 31;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{0, 50, 0, 0}};
  int ret = s21_add(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_add_test_10) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal var2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_add(var1, var2, &result);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_add_test_11) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b000000000000000000000000000000010;
  value_1.bits[1] = 0b000000000000000000000000000000000;
  value_1.bits[2] = 0b000000000000000000000000000000000;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b000000000000000000000000000000101;
  value_2.bits[1] = 0b000000000000000000000000000000000;
  value_2.bits[2] = 0b000000000000000000000000000000000;
  value_2.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000111;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_add_test_12) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b000000000000000000000000010010100;
  value_1.bits[1] = 0b000000000000000000000000000000000;
  value_1.bits[2] = 0b000000000000000000000000000000000;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b000000000000000000000000000000001;
  value_2.bits[1] = 0b000000000000000000000000000000000;
  value_2.bits[2] = 0b000000000000000000000000000000000;
  value_2.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000010010101;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_add_test_13) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b000000000000000000000000000111111;
  value_1.bits[1] = 0b000000000000000001110001000000000;
  value_1.bits[2] = 0b000000000000000010000000000000000;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b000000000000000000000000000110111;
  value_2.bits[1] = 0b000000000000000000000000000000000;
  value_2.bits[2] = 0b000000000000000000000000000000000;
  value_2.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000001110110;
  fmtcheck.bits[1] = 0b00000000000000001110001000000000;
  fmtcheck.bits[2] = 0b00000000000000010000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_add_test_14) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b000000000000000000000000001100011;
  value_1.bits[1] = 0b000000000000000000000000000000000;
  value_1.bits[2] = 0b000000000000000000000000000000000;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b000000000000000000000000000000001;
  value_2.bits[1] = 0b000000000000000000000000000000000;
  value_2.bits[2] = 0b000000000000000000000000000000000;
  value_2.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000001100100;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_add_test_15) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000000000001;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000010;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_add_test_16) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b000000000000000000000000000000001;
  value_1.bits[1] = 0b000000000000000000000000000000000;
  value_1.bits[2] = 0b000000000000000000000000000000000;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000000;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_add_test_17) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b011111111111111111111111111111111;
  value_1.bits[1] = 0b011111111111111111111111111111111;
  value_1.bits[2] = 0b011111111111111111111111111111111;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b011111111111111111111111111111111;
  value_2.bits[1] = 0b011111111111111111111111111111111;
  value_2.bits[2] = 0b011111111111111111111111111111111;
  value_2.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal result = {0};

  int res = s21_add(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000000;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 1);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

// sub tests
START_TEST(s21_sub_test_1) {
  s21_decimal var1 = {{50, 50, 50, 0}};
  s21_decimal var2 = {{50, 50, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{0, 0, 50, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_2) {
  s21_decimal var1 = {{0, 50, 50, 0}};
  s21_decimal var2 = {{50, 50, 50, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal ch = {{50, 0, 0, 0}};
  ch.bits[3] = 1 << 31;
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_3) {
  s21_decimal var1 = {{7, 55, 0, 0}};
  var1.bits[3] = 6 << 16;
  s21_decimal var2 = {{30, 50, 0, 0}};
  var2.bits[3] = 7 << 16;
  s21_decimal ch = {{40, 500, 0, 0}};
  ch.bits[3] = 7 << 16;
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal var1 = {{7, 33, 0, 0}};
  var1.bits[3] = 1 << 31;
  s21_decimal var2 = {{10, 55, 0, 0}};
  var2.bits[3] = 1 << 31;
  s21_decimal ch = {{3, 22, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_5) {
  s21_decimal var1 = {{7, 33, 0, 0}};
  var1.bits[3] = 1 << 31;
  s21_decimal var2 = {{10, 55, 0, 0}};
  var2.bits[3] = 1 << 31;
  s21_decimal ch = {{3, 22, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_6) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000000000001;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {0};
  int res = s21_sub(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000010;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_7) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000000001110;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b00000000000000000000000000000111;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {0};
  int res = s21_sub(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000111;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_8) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {0};
  int res = s21_sub(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b0000000000000000000000000000011;
  fmtcheck.bits[1] = 0b0000000000000000000000000000000;
  fmtcheck.bits[2] = 000000000000000000000000000000000;
  fmtcheck.bits[3] = 0b0000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_9) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {0};
  int res = s21_sub(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000000;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_10) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b000000000000000000000000000000001;
  value_1.bits[1] = 0b000000000000000000000000000000000;
  value_1.bits[2] = 0b000000000000000000000000000000000;
  value_1.bits[3] = 0b000000000000000000000000000000000;
  s21_decimal value_2 = {0};
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {0};
  int res = s21_sub(value_2, value_1, &result);
  s21_decimal fmtcheck = {0};
  fmtcheck.bits[0] = 0b00000000000000000000000000000000;
  fmtcheck.bits[1] = 0b00000000000000000000000000000000;
  fmtcheck.bits[2] = 0b00000000000000000000000000000000;
  fmtcheck.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(res, 1);
  ck_assert_uint_eq(result.bits[0], fmtcheck.bits[0]);
  ck_assert_uint_eq(result.bits[1], fmtcheck.bits[1]);
  ck_assert_uint_eq(result.bits[2], fmtcheck.bits[2]);
  ck_assert_uint_eq(result.bits[3], fmtcheck.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_11) {
  s21_decimal var1 = {{70, 55, 0, 0}};
  var1.bits[3] = 1 << 31;
  var1.bits[3] |= (4 << 16);
  s21_decimal var2 = {{30, 50, 0, 0}};
  var2.bits[3] = 1 << 31;
  var2.bits[3] |= (3 << 16);
  s21_decimal ch = {{230, 445, 0, 0}};
  ch.bits[3] |= (4 << 16);
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_12) {
  s21_decimal var1 = {{50, 50, 50, 0}};
  s21_decimal var2 = {{50, 50, 50, 0}};
  var2.bits[3] = 1 << 31;
  s21_decimal ch = {{100, 100, 100, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_13) {
  s21_decimal var1 = {{0, 0, 0, 0}};
  s21_decimal var2 = {{0, 0, 0, 0}};
  s21_decimal ch = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_14) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  var1.bits[3] = 1 << 31;
  s21_decimal var2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_sub_test_15) {
  s21_decimal var1 = {{7, 55, 0, 0}};
  var1.bits[3] = 1 << 31;
  s21_decimal var2 = {{30, 50, 0, 0}};
  var2.bits[3] = 1 << 31;
  var2.bits[3] |= (2 << 16);
  s21_decimal ch = {{670, 5450, 0, 0}};
  ch.bits[3] = 1 << 31;
  ch.bits[3] |= (2 << 16);
  s21_decimal result = {{0, 0, 0, 0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_16) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  var1.bits[3] = 1 << 31;
  s21_decimal var2 = {{6, 0, 0, 0}};
  var2.bits[3] |= (1 << 16);
  s21_decimal ch = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 1);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_17) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal var2 = {{6, 0, 0, 0}};
  var2.bits[3] |= (1 << 16);
  s21_decimal ch = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal result = {{0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_sub_test_18) {
  s21_decimal var1 = {{15, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal var2 = {{15, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal ch = {{0, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal result = {{0}};
  int ret = s21_sub(var1, var2, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_uint_eq(result.bits[0], ch.bits[0]);
  ck_assert_uint_eq(result.bits[1], ch.bits[1]);
  ck_assert_uint_eq(result.bits[2], ch.bits[2]);
  ck_assert_uint_eq(result.bits[3], ch.bits[3]);
}
END_TEST

START_TEST(s21_negate_test_1) {
  s21_decimal val1 = {{1123, 12385, 12489, 0}};
  s21_decimal val2 = {{1123, 12385, 12489, 0}};
  val2.bits[3] = 0b10000000000000000000000000000000;
  int res = s21_negate(val1, &val1);
  ck_assert_int_eq(0, res);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[1], val1.bits[1]);
  ck_assert_uint_eq(val2.bits[2], val1.bits[2]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_negate_test_2) {
  s21_decimal val1 = {{12391087, 134, 111, 0b10000000000000000000000000000000}};
  s21_decimal val2 = {{12391087, 134, 111, 0}};
  val2.bits[3] = 0b00000000000000000000000000000000;
  int res = s21_negate(val1, &val1);
  ck_assert_int_eq(0, res);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[1], val1.bits[1]);
  ck_assert_uint_eq(val2.bits[2], val1.bits[2]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_negate_test_3) {
  s21_decimal val1 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal val2 = {{0}};
  val2.bits[3] = 0b00000000000000110000000000000000;
  int res = s21_negate(val1, &val1);
  ck_assert_int_eq(0, res);
  ck_assert_uint_eq(val2.bits[0], val1.bits[0]);
  ck_assert_uint_eq(val2.bits[1], val1.bits[1]);
  ck_assert_uint_eq(val2.bits[2], val1.bits[2]);
  ck_assert_uint_eq(val2.bits[3], val1.bits[3]);
}
END_TEST

START_TEST(s21_mul_test_1) {
  s21_decimal val1 = {{2}};
  s21_decimal val2 = {{2}};
  s21_decimal res_core = {{4}};
  s21_decimal result_test = {{0}};
  int res = s21_mul(val1, val2, &result_test);
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(res_core.bits[0], result_test.bits[0]);
  ck_assert_uint_eq(res_core.bits[1], result_test.bits[1]);
  ck_assert_uint_eq(res_core.bits[2], result_test.bits[2]);
  ck_assert_uint_eq(res_core.bits[3], result_test.bits[3]);
}
END_TEST

START_TEST(s21_mul_test_2) {
  s21_decimal val1 = {{19000000}};
  s21_decimal val2 = {{10000000}};
  s21_decimal res_core = {
      {0b11010010100000011110000000000000, 0b1010110011001101}};
  s21_decimal result_test = {{0}};
  int res = s21_mul(val1, val2, &result_test);
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(res_core.bits[0], result_test.bits[0]);
  ck_assert_uint_eq(res_core.bits[1], result_test.bits[1]);
  ck_assert_uint_eq(res_core.bits[2], result_test.bits[2]);
  ck_assert_uint_eq(res_core.bits[3], result_test.bits[3]);
}
END_TEST

START_TEST(s21_mul_test_3) {
  s21_decimal val1 = {{195436566, 123435457, 1248219}};
  s21_decimal val2 = {{999800000, 123123, 65475}};
  s21_decimal res_core = {{0}};
  s21_decimal result_test = {{0}};
  int res = s21_mul(val1, val2, &result_test);
  ck_assert_int_eq(res, 1);
  ck_assert_uint_eq(res_core.bits[0], result_test.bits[0]);
  ck_assert_uint_eq(res_core.bits[1], result_test.bits[1]);
  ck_assert_uint_eq(res_core.bits[2], result_test.bits[2]);
  ck_assert_uint_eq(res_core.bits[3], result_test.bits[3]);
}
END_TEST

START_TEST(s21_mul_test_4) {
  s21_decimal val1 = {{19000000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal val2 = {{10000000}};
  s21_decimal res_core = {{0b11010010100000011110000000000000,
                           0b1010110011001101, 0,
                           0b10000000000000000000000000000000}};
  s21_decimal result_test = {{0}};
  int res = s21_mul(val1, val2, &result_test);
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(res_core.bits[0], result_test.bits[0]);
  ck_assert_uint_eq(res_core.bits[1], result_test.bits[1]);
  ck_assert_uint_eq(res_core.bits[2], result_test.bits[2]);
  ck_assert_uint_eq(res_core.bits[3], result_test.bits[3]);
}
END_TEST

START_TEST(s21_mul_test_5) {
  s21_decimal val1 = {{19000000, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal val2 = {{10000000, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal res_core = {{0b11010010100000011110000000000000,
                           0b1010110011001101, 0,
                           0b10000000000001100000000000000000}};
  s21_decimal result_test = {{0}};
  int res = s21_mul(val1, val2, &result_test);
  ck_assert_int_eq(res, 0);
  ck_assert_uint_eq(res_core.bits[0], result_test.bits[0]);
  ck_assert_uint_eq(res_core.bits[1], result_test.bits[1]);
  ck_assert_uint_eq(res_core.bits[2], result_test.bits[2]);
  ck_assert_uint_eq(res_core.bits[3], result_test.bits[3]);
}
END_TEST

START_TEST(s21_mul_test_6) {
  s21_decimal val1 = {{89000000, 0, 0, 0b10000000000111110000000000000000}};
  s21_decimal val2 = {{13247000, 0, 0, 0b00000000001111110000000000000000}};
  s21_decimal res_core = {{0}};
  s21_decimal result_test = {{0}};
  int res = s21_mul(val1, val2, &result_test);
  ck_assert_int_eq(res, 2);
  ck_assert_uint_eq(res_core.bits[0], result_test.bits[0]);
  ck_assert_uint_eq(res_core.bits[1], result_test.bits[1]);
  ck_assert_uint_eq(res_core.bits[2], result_test.bits[2]);
  ck_assert_uint_eq(res_core.bits[3], result_test.bits[3]);
}
END_TEST

Suite *s21_mul_suite(void) {
  TCase *tc = tcase_create("s21_mul_core");
  Suite *s = suite_create("s21_mul_tests");

  tcase_add_test(tc, s21_mul_test_1);
  tcase_add_test(tc, s21_mul_test_2);
  tcase_add_test(tc, s21_mul_test_3);
  tcase_add_test(tc, s21_mul_test_4);
  tcase_add_test(tc, s21_mul_test_5);
  tcase_add_test(tc, s21_mul_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_negate_suite(void) {
  TCase *tc = tcase_create("s21_negate_core");
  Suite *s = suite_create("s21_negate_tests");

  tcase_add_test(tc, s21_negate_test_1);
  tcase_add_test(tc, s21_negate_test_2);
  tcase_add_test(tc, s21_negate_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sub_suite(void) {
  TCase *tc = tcase_create("s21_sub_core");
  Suite *s = suite_create("s21_sub_tests");

  tcase_add_test(tc, s21_sub_test_1);
  tcase_add_test(tc, s21_sub_test_2);
  tcase_add_test(tc, s21_sub_test_3);
  tcase_add_test(tc, s21_sub_test_4);
  tcase_add_test(tc, s21_sub_test_5);
  tcase_add_test(tc, s21_sub_test_6);
  tcase_add_test(tc, s21_sub_test_7);
  tcase_add_test(tc, s21_sub_test_8);
  tcase_add_test(tc, s21_sub_test_9);
  tcase_add_test(tc, s21_sub_test_10);
  tcase_add_test(tc, s21_sub_test_11);
  tcase_add_test(tc, s21_sub_test_12);
  tcase_add_test(tc, s21_sub_test_13);
  tcase_add_test(tc, s21_sub_test_14);
  tcase_add_test(tc, s21_sub_test_15);
  tcase_add_test(tc, s21_sub_test_16);
  tcase_add_test(tc, s21_sub_test_17);
  tcase_add_test(tc, s21_sub_test_18);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_add_suite(void) {
  TCase *tc = tcase_create("s21_add_core");
  Suite *s = suite_create("s21_add_tests");

  tcase_add_test(tc, s21_add_test_1);
  tcase_add_test(tc, s21_add_test_2);
  tcase_add_test(tc, s21_add_test_3);
  tcase_add_test(tc, s21_add_test_4);
  tcase_add_test(tc, s21_add_test_5);
  tcase_add_test(tc, s21_add_test_6);
  tcase_add_test(tc, s21_add_test_7);
  tcase_add_test(tc, s21_add_test_8);
  tcase_add_test(tc, s21_add_test_9);
  tcase_add_test(tc, s21_add_test_10);
  tcase_add_test(tc, s21_add_test_11);
  tcase_add_test(tc, s21_add_test_12);
  tcase_add_test(tc, s21_add_test_13);
  tcase_add_test(tc, s21_add_test_14);
  tcase_add_test(tc, s21_add_test_15);
  tcase_add_test(tc, s21_add_test_16);
  tcase_add_test(tc, s21_add_test_17);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_from_decimal_to_float_suite(void) {
  TCase *tc = tcase_create("s21_from_decimal_to_float_core");
  Suite *s = suite_create("s21_from_decimal_to_float_tests");

  tcase_add_test(tc, s21_from_decimal_to_float_test_1);
  tcase_add_test(tc, s21_from_decimal_to_float_test_2);
  tcase_add_test(tc, s21_from_decimal_to_float_test_3);
  tcase_add_test(tc, s21_from_decimal_to_float_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_from_float_to_dec_suite(void) {
  TCase *tc = tcase_create("s21_from_float_to_dec_core");
  Suite *s = suite_create("s21_from_float_to_dec_tests");

  tcase_add_test(tc, s21_from_float_to_decimal_test_1);
  tcase_add_test(tc, s21_from_float_to_decimal_test_2);
  tcase_add_test(tc, s21_from_float_to_decimal_test_3);
  tcase_add_test(tc, s21_from_float_to_decimal_test_4);
  tcase_add_test(tc, s21_from_float_to_decimal_test_5);
  tcase_add_test(tc, s21_from_float_to_decimal_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_div_suite(void) {
  TCase *tc = tcase_create("s21_div_core");
  Suite *s = suite_create("s21_div_tests");

  tcase_add_test(tc, s21_div_test_1);
  tcase_add_test(tc, s21_div_test_2);
  tcase_add_test(tc, s21_div_test_3);
  tcase_add_test(tc, s21_div_test_4);
  tcase_add_test(tc, s21_div_test_5);
  tcase_add_test(tc, s21_div_test_6);
  tcase_add_test(tc, s21_div_test_7);
  tcase_add_test(tc, s21_div_test_8);
  tcase_add_test(tc, s21_div_test_9);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_from_decimal_to_int_suite(void) {
  TCase *tc = tcase_create("s21_from_decimal_to_int_core");
  Suite *s = suite_create("s21_from_decimal_to_int_tests");

  tcase_add_test(tc, s21_from_decimal_to_int_test_1);
  tcase_add_test(tc, s21_from_decimal_to_int_test_2);
  tcase_add_test(tc, s21_from_decimal_to_int_test_3);
  tcase_add_test(tc, s21_from_decimal_to_int_test_4);
  tcase_add_test(tc, s21_from_decimal_to_int_test_5);
  tcase_add_test(tc, s21_from_decimal_to_int_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_from_int_to_decimal_suite(void) {
  TCase *tc = tcase_create("s21_from_int_to_decimal_core");
  Suite *s = suite_create("s21_from_int_to_decimal_tests");

  tcase_add_test(tc, s21_from_int_to_decimal_test_1);
  tcase_add_test(tc, s21_from_int_to_decimal_test_2);
  tcase_add_test(tc, s21_from_int_to_decimal_test_3);
  tcase_add_test(tc, s21_from_int_to_decimal_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_round_suite(void) {
  TCase *tc = tcase_create("s21_round_core");
  Suite *s = suite_create("s21_round_tests");

  tcase_add_test(tc, s21_round_test_1);
  tcase_add_test(tc, s21_round_test_2);
  tcase_add_test(tc, s21_round_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_floor_suite(void) {
  TCase *tc = tcase_create("s21_floor_core");
  Suite *s = suite_create("s21_floor_tests");

  tcase_add_test(tc, s21_floor_test_1);
  tcase_add_test(tc, s21_floor_test_2);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_truncate_suite(void) {
  TCase *tc = tcase_create("s21_truncate_core");
  Suite *s = suite_create("s21_truncate_tests");

  tcase_add_test(tc, s21_truncate_test_1);
  tcase_add_test(tc, s21_truncate_test_2);
  tcase_add_test(tc, s21_truncate_test_3);
  tcase_add_test(tc, s21_truncate_test_4);
  tcase_add_test(tc, s21_truncate_test_5);
  tcase_add_test(tc, s21_truncate_test_6);
  tcase_add_test(tc, s21_truncate_test_7);
  tcase_add_test(tc, s21_truncate_test_8);
  tcase_add_test(tc, s21_truncate_test_9);
  tcase_add_test(tc, s21_truncate_test_10);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_is_less_or_equal_suite(void) {
  TCase *tc = tcase_create("s21_is_less_or_equl_core");
  Suite *s = suite_create("s21_is_less_or_equal_tests");

  tcase_add_test(tc, s21_is_less_or_equal_test_1);
  tcase_add_test(tc, s21_is_less_or_equal_test_2);
  tcase_add_test(tc, s21_is_less_or_equal_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_is_less_suite(void) {
  TCase *tc = tcase_create("s21_is_less_core");
  Suite *s = suite_create("s21_is_less_tests");

  tcase_add_test(tc, s21_is_less_test_1);
  tcase_add_test(tc, s21_is_less_test_2);
  tcase_add_test(tc, s21_is_less_test_3);
  tcase_add_test(tc, s21_is_less_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_is_greater_or_equal_suite(void) {
  TCase *tc = tcase_create("s21_is_greater_or_equal_core");
  Suite *s = suite_create("s21_is_greater_or_equal_tests");

  tcase_add_test(tc, s21_is_greater_or_equal_test_1);
  tcase_add_test(tc, s21_is_greater_or_equal_test_2);
  tcase_add_test(tc, s21_is_greater_or_equal_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_is_greater_suite(void) {
  TCase *tc = tcase_create("s21_is_greater_core");
  Suite *s = suite_create("s21_is_greater_tests");

  tcase_add_test(tc, s21_is_greater_test_1);
  tcase_add_test(tc, s21_is_greater_test_2);
  tcase_add_test(tc, s21_is_greater_test_3);
  tcase_add_test(tc, s21_is_greater_test_4);
  tcase_add_test(tc, s21_is_greater_test_5);
  tcase_add_test(tc, s21_is_greater_test_6);
  tcase_add_test(tc, s21_is_greater_test_7);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_is_not_equal_suite(void) {
  TCase *tc = tcase_create("s21_is_not_equal_core");
  Suite *s = suite_create("s21_is_not_equal_tests");

  tcase_add_test(tc, s21_is_not_equal_test_1);
  tcase_add_test(tc, s21_is_not_equal_test_2);
  tcase_add_test(tc, s21_is_not_equal_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_is_equal_suite(void) {
  TCase *tc = tcase_create("s21_is_equal_core");
  Suite *s = suite_create("s21_is_equal_tests");

  tcase_add_test(tc, s21_is_equal_test_1);
  tcase_add_test(tc, s21_is_equal_test_2);
  tcase_add_test(tc, s21_is_equal_test_3);
  tcase_add_test(tc, s21_is_equal_test_4);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr;

  sr = srunner_create(s21_is_equal_suite());
  srunner_add_suite(sr, s21_is_not_equal_suite());
  srunner_add_suite(sr, s21_is_greater_suite());
  srunner_add_suite(sr, s21_is_greater_or_equal_suite());
  srunner_add_suite(sr, s21_is_less_suite());
  srunner_add_suite(sr, s21_is_less_or_equal_suite());
  srunner_add_suite(sr, s21_truncate_suite());
  srunner_add_suite(sr, s21_floor_suite());
  srunner_add_suite(sr, s21_round_suite());
  srunner_add_suite(sr, s21_from_int_to_decimal_suite());
  srunner_add_suite(sr, s21_from_decimal_to_int_suite());
  srunner_add_suite(sr, s21_div_suite());
  srunner_add_suite(sr, s21_from_float_to_dec_suite());
  srunner_add_suite(sr, s21_add_suite());
  srunner_add_suite(sr, s21_sub_suite());
  srunner_add_suite(sr, s21_from_decimal_to_float_suite());
  srunner_add_suite(sr, s21_mul_suite());
  srunner_add_suite(sr, s21_negate_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}
