
#include "s21_decimal.h"

int s21_for_rounding(s21_decimal value, s21_decimal* result, int floor,
                     int round) {
  int res = 0;
  int degree = s21_decimal_degree(value.bits[3]);
  s21_decimal_clean(result);

  if (s21_dec_last_bit_zero_check(value) || degree >= 29) {
    res = 1;
  }

  if (!res) {
    int negative = s21_get_bit(value.bits[3], 31);
    int is_rest = 0;
    int rest = 0;
    s21_big_decimal dec_big_rest = {{0}}, value_big = {{0}};
    s21_decimal dec_rest = {{0}};

    s21_to_big(value, &value_big);

    for (int i = 0; i < degree; i++) {
      rest = s21_div_by_ten(value_big, &value_big, 1);
      if (rest != -1) {
        is_rest = 1;
        s21_from_int_to_decimal(rest, &dec_rest);
        s21_to_big(dec_rest, &dec_big_rest);
        s21_big_sub(value_big, dec_big_rest, &value_big);
        s21_div_by_ten(value_big, &value_big, 0);
      }
    }

    if ((rest >= 5 && round && !negative) || (negative && is_rest && floor)) {
      s21_big_decimal add = {{1, 0, 0, 0, 0, 0, 0}};
      s21_big_add(value_big, add, &value_big);
    }

    for (int b = 0; b < 3; b++) {
      result->bits[b] = value_big.bits[b];
    }
    if (negative) s21_set_bit_32(&result->bits[3], 31);
  }
  return res;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  return s21_for_rounding(value, result, 0, 0);
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  return s21_for_rounding(value, result, 1, 0);
}

int s21_round(s21_decimal value, s21_decimal* result) {
  return s21_for_rounding(value, result, 0, 1);
}
