#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  *dst = 0;
  s21_truncate(src, &src);
  int max = -1;
  for (int i = 95; max == -1 && i >= 0; i--) {
    if (s21_get_bit(src.bits[i / 32], i % 32)) {
      max = i;
    }
  }
  if (max >= 32) {
    res = 1;
  } else {
    int neg = s21_get_bit(src.bits[3], 31);
    if ((neg && src.bits[0] <= (unsigned)(S21_INT_MAX) + 1) ||
        (!neg && src.bits[0] <= (unsigned)S21_INT_MAX)) {
      for (int i = 0; i < 31; i++) {
        int bit = s21_get_bit(src.bits[0], i);
        if (bit) {
          s21_set_bit_32((unsigned *)dst, i);
        } else {
          s21_clear_bit_32((unsigned *)dst, i);
        }
      }
      if (neg) {
        if (src.bits[0] == (unsigned)S21_INT_MAX + 1) {
          *dst = S21_INT_MIN;
        } else {
          *dst *= -1;
        }
      }
    } else {
      res = 1;
    }
  }
  return res;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  int k = 0, znak = 0;
  s21_big_decimal big_value_1 = {{0}};
  s21_big_decimal big_value_2 = {{0}};
  s21_big_decimal big_result = {{0}};
  s21_to_big(value_1, &big_value_1);
  s21_to_big(value_2, &big_value_2);
  if ((s21_get_bit(value_1.bits[3], 31) &&
       s21_get_bit(value_2.bits[3], 31) == 0) ||
      (s21_get_bit(value_1.bits[3], 31) == 0 &&
       s21_get_bit(value_2.bits[3], 31))) {
    znak = 1;
  }
  s21_big_decimal sum = {{0}};
  s21_decimal_clean(result);
  for (int b = 0; b < 3; b++) {
    for (int i = 0; i < 32; i++) {
      if (s21_get_bit(big_value_2.bits[b], i) == 0) {
        continue;
      } else {
        s21_big_copy(big_result, &sum);
        if (s21_big_left_shift(&big_value_1, i - k)) res = 1;
        k = i;
        s21_big_add(sum, big_value_1, &big_result);
      }
    }
  }
  s21_degree_add(&big_result, s21_decimal_degree(big_value_1.bits[6]) +
                                  s21_decimal_degree(big_value_2.bits[6]));
  if (znak == 0) {
    s21_clear_bit_32(&big_result.bits[6], 31);
  } else if (znak) {
    s21_set_bit_32(&big_result.bits[6], 31);
  }
  res = s21_big_to_dec(big_result, result);
  return res;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int degree = s21_decimal_degree(value.bits[3]);
  if (s21_dec_last_bit_zero_check(value) || degree >= 29) {
    res = 1;
    s21_decimal_clean(result);
  } else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    if (s21_get_bit(value.bits[3], 31)) {
      s21_clear_bit_32(&result->bits[3], 31);
    } else if (s21_get_bit(value.bits[3], 31) == 0) {
      s21_set_bit_32(&result->bits[3], 31);
    }
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  int index = -1;
  int degree = s21_decimal_degree(src.bits[3]);
  double num = 0;

  for (int i = 95; i >= 0 && index == -1; i--) {
    if (s21_get_bit(src.bits[i / 32], i % 32)) {
      index = i;
    }
  }

  for (int i = 0; i <= index; i++) {
    num += pow(2, i) * s21_get_bit(src.bits[i / 32], i % 32);
  }
  num /= pow(10, degree);
  if (s21_get_bit(src.bits[3], 31)) {
    num *= -1;
  }

  *dst = num;

  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0, len = 0, degree_flag = 0, degree_counter = 0, zero = 0, znak = 0;
  s21_big_decimal result = {{0}};
  char *str = calloc(150, sizeof(char));
  s21_decimal_clean(dst);
  if (src < 0) {
    znak = 1;
  }
  if ((fabs(src) > 0 && fabs(src) < 1e-28) || fabs(src) >= pow(2, 96)) {
    res = 1;
  } else {
    sprintf(str, "%.7f", src);
    len = strlen(str);
    str[len] = '\0';
    int j = len;
    for (int i = len - 1; i >= 0; i--) {
      if (str[i] == '0' && j == i + 1) {
        j = i;
        zero++;
        continue;
      } else {
        if (str[i] == '.') {
          degree_flag = 1;
        } else if (str[i] != '.' && degree_flag == 0) {
          degree_counter++;
        }
        s21_from_str_to_decimal(str[i], &result,
                                len - 1 - i - zero - degree_flag);
      }
    }
    s21_big_to_dec(result, dst);
    dst->bits[3] = degree_counter <<= 16;
    if (znak) {
      s21_set_bit_32(&dst->bits[3], 31);
    }
  }
  free(str);
  return res;
}

void s21_from_str_to_decimal(char str, s21_big_decimal *dst, int c) {
  if (str != '.' && str != '-') {
    s21_big_decimal tmp = {{str - 48}};
    for (int i = 0; i < c; i++) {
      s21_mult_by_ten(tmp, &tmp);
    }
    s21_big_add(tmp, *dst, dst);
  }
}
