#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  s21_big_decimal value_1_big = {{0}}, value_2_big = {{0}};

  s21_to_big(value_1, &value_1_big);
  s21_to_big(value_2, &value_2_big);
  s21_dec_equalize(&value_1_big, &value_2_big);

  for (int b = 0; b < 7 && res; b++) {
    for (int i = 0; i < 32 && res; ++i) {
      if (s21_get_bit(value_1_big.bits[b], i) !=
          s21_get_bit(value_2_big.bits[b], i)) {
        res = 0;
      }
    }
  }
  return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = s21_is_equal(value_1, value_2) == 1 ? 0 : 1;
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  int got = 0;
  int val1_neg = s21_get_bit(value_1.bits[3], 31);
  int val2_neg = s21_get_bit(value_2.bits[3], 31);

  s21_big_decimal value_1_big = {{0}}, value_2_big = {{0}};
  s21_to_big(value_1, &value_1_big);
  s21_to_big(value_2, &value_2_big);
  s21_dec_equalize(&value_1_big, &value_2_big);

  if (s21_is_equal(value_1, value_2) || (val1_neg && (!val2_neg))) {
    res = 0;
    got = 1;
  }

  if ((!val1_neg) && val2_neg) {
    got = 1;
  }

  for (int b = 5; b >= 0 && !got; b--) {
    for (int i = 31; i >= 0 && !got; i--) {
      if (s21_get_bit(value_1_big.bits[b], i) ==
          s21_get_bit(value_2_big.bits[b], i)) {
        continue;
      }
      if ((s21_get_bit(value_1_big.bits[b], i) == 0) &&
          (s21_get_bit(value_2_big.bits[b], i) == 1)) {
        res = 0;
      }
      got = 1;
    }
  }
  if (val1_neg && val2_neg) {
    res = res == 1 ? 0 : 1;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = s21_is_greater(value_1, value_2) == 1 ||
                    s21_is_equal(value_1, value_2) == 1
                ? 1
                : 0;
  return res;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int res = s21_is_greater(value_1, value_2) == 1 ||
                    s21_is_equal(value_1, value_2) == 1
                ? 0
                : 1;
  return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  res =
      s21_is_less(value_1, value_2) == 1 || s21_is_equal(value_1, value_2) == 1
          ? 1
          : 0;
  return res;
}

int s21_is_less_32(unsigned int a, unsigned int b) {
  int res = 0;
  int flag = 1;
  for (int i = 31; flag && i >= 0; i--) {
    if (!s21_get_bit(a, i) && s21_get_bit(b, i)) {
      res = 1;
      flag = 0;
    } else if (s21_get_bit(a, i) && !s21_get_bit(b, i)) {
      flag = 0;
    }
  }
  return res;
}

int s21_big_is_less(s21_big_decimal a, s21_big_decimal b) {
  int res = 0;
  int flag = 1;
  for (int i = 191; flag && i >= 0; i--) {
    if (!s21_get_bit(a.bits[i / 32], i % 32) &&
        s21_get_bit(b.bits[i / 32], i % 32)) {
      res = 1;
      flag = 0;
    } else if (s21_get_bit(a.bits[i / 32], i % 32) &&
               !s21_get_bit(b.bits[i / 32], i % 32)) {
      flag = 0;
    }
  }
  return res;
}
