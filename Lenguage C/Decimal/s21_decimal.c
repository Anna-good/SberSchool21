#include "s21_decimal.h"

// int main() {
//   float a = 15;
//   s21_decimal res = {{0}};
//   s21_from_float_to_decimal(a, &res);
// }

int s21_get_bit(unsigned int x, unsigned int index) {
  int res = 0;
  if (index > 31) {
    res = -1;
  } else {
    res = 1 & (x >> index);
  }
  return res;
}

int s21_set_bit_32(unsigned int* x, unsigned index) {
  int res = 1;
  if (index > 31) {
    res = -1;
  } else {
    *x |= 1 << index;
  }
  return res;
}

int s21_clear_bit_32(unsigned int* x, unsigned index) {
  int res = 1;
  if (index > 31) {
    res = -1;
  } else {
    (*x) &= ~(~(*x) | (1 << index));
  }
  return res;
}

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int res = 0;
  int add = 0;
  s21_decimal_clean(dst);
  if (src < 0) {
    if (src == S21_INT_MIN) {
      add++;
    }
    src = (src + add) * -1;
    s21_set_bit_32(&dst->bits[3], 31);
  }
  for (int i = 0; i < 31; i++) {
    int bit = s21_get_bit(src, i);
    if (bit) {
      s21_set_bit_32(&dst->bits[0], i);
    } else {
      s21_clear_bit_32(&dst->bits[0], i);
    }
  }
  if (add) {
    int change = 0;
    s21_add_32(dst->bits[0], add, &dst->bits[0], &change);
  }
  return res;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int res = 0;
  if (!s21_get_bit(value_1.bits[3], 31) && s21_get_bit(value_2.bits[3], 31)) {
    s21_clear_bit_32(&value_2.bits[3], 31);
    res = s21_sub(value_1, value_2, result);
  } else if (s21_get_bit(value_1.bits[3], 31) &&
             !s21_get_bit(value_2.bits[3], 31)) {
    s21_clear_bit_32(&value_1.bits[3], 31);
    res = s21_sub(value_2, value_1, result);
  } else {
    s21_big_decimal v_1;
    s21_big_decimal v_2;
    s21_big_decimal big_res;
    s21_to_big(value_1, &v_1);
    s21_to_big(value_2, &v_2);
    s21_dec_equalize(&v_1, &v_2);
    s21_big_add(v_1, v_2, &big_res);
    if (s21_big_to_dec(big_res, result)) {
      res = 1;
      s21_decimal_clean(result);
    }
  }
  return res;
}

int s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result) {
  int change = 0;
  int res = 0;
  for (int b = 0; b < 6; b++) {
    s21_add_32(value_1.bits[b], value_2.bits[b], &result->bits[b], &change);
  }
  result->bits[6] = value_1.bits[6];
  return res;
}

void s21_add_32(unsigned int value_1, unsigned int value_2,
                unsigned int* result, int* change) {
  int tmp = 0;
  for (int i = 0; i < 32; i++) {
    tmp = s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + *change;
    if (tmp == 0 || tmp == 2) {
      s21_clear_bit_32(result, i);
      *change = tmp == 2 ? 1 : 0;
    } else {
      s21_set_bit_32(result, i);
      *change = tmp == 3 ? 1 : 0;
    }
  }
}

int s21_mult_by_ten(s21_big_decimal value, s21_big_decimal* res) {
  int flag = 1;
  s21_big_decimal sh_1 = {{0}};
  s21_big_copy(value, &sh_1);
  s21_big_decimal sh_2 = {{0}};
  s21_big_copy(value, &sh_2);
  if (!s21_big_left_shift(&sh_1, 1) && !s21_big_left_shift(&sh_2, 3)) {
    s21_big_add(sh_1, sh_2, res);
    flag = 0;
  }
  return flag;
}

int s21_big_left_shift(s21_big_decimal* res, int k) {
  int flag = 0;
  for (int i = 191; i >= 0 && !flag; i--) {
    int tmp = s21_get_bit(res->bits[i / 32], i % 32);
    if (i + k < 192) {
      if (tmp) {
        s21_set_bit_32(&res->bits[(i + k) / 32], (i + k) % 32);
      } else {
        s21_clear_bit_32(&res->bits[(i + k) / 32], (i + k) % 32);
      }
    } else {
      if (tmp) {
        flag = 1;
      }
    }
    s21_clear_bit_32(&res->bits[i / 32], i % 32);
  }
  return flag;
}

void s21_decimal_clean(s21_decimal* dec) {
  for (int b = 0; b < 4; b++) {
    dec->bits[b] = 0;
  }
}

int s21_decimal_degree(unsigned int dec) {
  int res = 0;
  int count = 1;
  for (int i = 16; i < 24; i++) {
    count *= i == 16 ? 1 : 2;
    res += count * s21_get_bit(dec, i);
  }
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int res = 0;
  if (s21_get_bit(value_1.bits[3], 31) && !s21_get_bit(value_2.bits[3], 31)) {
    s21_set_bit_32(&value_2.bits[3], 31);
    res = s21_add(value_1, value_2, result);
  } else if (!s21_get_bit(value_1.bits[3], 31) &&
             s21_get_bit(value_2.bits[3], 31)) {
    s21_clear_bit_32(&value_2.bits[3], 31);
    res = s21_add(value_1, value_2, result);
  } else if (s21_get_bit(value_1.bits[3], 31) &&
             s21_get_bit(value_2.bits[3], 31)) {
    s21_clear_bit_32(&value_2.bits[3], 31);
    s21_clear_bit_32(&value_1.bits[3], 31);
    res = s21_sub(value_2, value_1, result);
  } else if (s21_is_less(value_1, value_2)) {
    res = s21_sub(value_2, value_1, result);
    if (!res) s21_set_bit_32(&result->bits[3], 31);
  } else {
    s21_big_decimal v_1;
    s21_big_decimal v_2;
    s21_big_decimal big_res;
    s21_to_big(value_1, &v_1);
    s21_to_big(value_2, &v_2);
    s21_dec_equalize(&v_1, &v_2);
    s21_big_sub(v_1, v_2, &big_res);
    s21_degree_add(&big_res, s21_decimal_degree(v_1.bits[6]));
    res = s21_big_to_dec(big_res, result);
    if (res == 1 || res == 2) {
      s21_decimal_clean(result);
    }
  }
  return res;
}

int s21_dec_last_bit_zero_check(s21_decimal dec) {
  int res = 0;
  for (int i = 0; !res && i < 16; i++) {
    if (s21_get_bit(dec.bits[3], i)) {
      res = 1;
    }
  }
  for (int i = 24; !res && i < 31; i++) {
    if (s21_get_bit(dec.bits[3], i)) {
      res = 1;
    }
  }
  return res;
}

int s21_degree_add(s21_big_decimal* dec, unsigned int num) {
  num <<= 16;
  int change = 0;
  s21_add_32(dec->bits[6], num, &dec->bits[6], &change);
  return 0;
}

int s21_to_big(s21_decimal dec, s21_big_decimal* res) {
  s21_big_clean(res);
  for (int b = 0; b < 7; b++) {
    if (b < 3) {
      res->bits[b] = dec.bits[b];
    } else if (b != 6) {
      res->bits[b] = 0;
    } else {
      res->bits[b] = dec.bits[b - 3];
    }
  }
  return 0;
}

int s21_dec_equalize(s21_big_decimal* res_1, s21_big_decimal* res_2) {
  int d1 = s21_decimal_degree(res_1->bits[6]);
  int d2 = s21_decimal_degree(res_2->bits[6]);
  int count = 0;
  s21_big_decimal tmp = {{0}};
  if (d1 > d2) {
    count = d1 - d2;
    for (int i = 0; i < count; i++) {
      s21_big_copy(*res_2, &tmp);
      s21_mult_by_ten(tmp, res_2);
    }
    s21_degree_add(res_2, (unsigned int)count);
  } else if (d1 < d2) {
    count = d2 - d1;
    for (int i = 0; i < count; i++) {
      s21_big_copy(*res_1, &tmp);
      s21_mult_by_ten(tmp, res_1);
    }
    s21_degree_add(res_1, (unsigned int)count);
  }
  return count;
}

void s21_big_copy(s21_big_decimal src, s21_big_decimal* dst) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = src.bits[i];
  }
}

int s21_find_max(s21_big_decimal src) {
  int res = -1;
  for (int i = 191; res == -1 && i >= 0; i--) {
    if (s21_get_bit(src.bits[i / 32], i % 32)) {
      res = i;
    }
  }
  return res;
}

void s21_big_right_shift(s21_big_decimal* res, int k) {
  if (k > 0) {
    for (int i = 0; i < 192; i++) {
      int tmp = s21_get_bit(res->bits[i / 32], i % 32);
      if (i - k >= 0) {
        if (tmp) {
          s21_set_bit_32(&res->bits[(i - k) / 32], (i - k) % 32);
        } else {
          s21_clear_bit_32(&res->bits[(i - k) / 32], (i - k) % 32);
        }
      }
      s21_clear_bit_32(&res->bits[i / 32], i % 32);
    }
  }
}

int s21_div_by_ten(s21_big_decimal value, s21_big_decimal* res, int mode) {
  int result = -1;
  s21_big_decimal dev = {{10}};
  s21_big_decimal tmp = {{0}};
  s21_big_copy(value, &tmp);
  s21_big_clean(res);
  int flag = s21_find_max(value);
  int count = 0;
  if (flag != -1) {
    if (flag >= 3) {
      flag -= 3;
      s21_big_right_shift(&tmp, flag);
    }
    int stop = 0;
    do {
      int k = 0;
      int sh = 0;
      while (s21_is_less_32(tmp.bits[0], dev.bits[0]) && flag > 0) {
        k++;
        flag--;
        s21_div_add_bit(value, &tmp, flag);
        if (k > 1 && count > 0) {
          sh++;
        }
      }
      if (flag == 0 && tmp.bits[0] != 0 &&
          s21_is_less_32(tmp.bits[0], dev.bits[0])) {
        s21_big_clean(res);
        s21_big_copy(value, res);
        stop++;
        if (!mode) {
          s21_degree_add(res, 1);
        } else {
          result = tmp.bits[0];
        }
      } else {
        sh++;
        s21_big_left_shift(res, sh);
        if (flag >= 0 && tmp.bits[0] != 0) {
          s21_set_bit_32(&res->bits[0], 0);
          s21_big_sub(tmp, dev, &tmp);
        }
        if (flag == 0 && tmp.bits[0] == 0) {
          res->bits[6] = value.bits[6];
          stop++;
        }
      }
      count++;
    } while (!stop);
  }
  return result;
}

int s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result) {
  int tmp = 0;
  int over = 0;
  s21_big_clean(result);
  if (s21_get_bit(value_1.bits[6], 31)) {
    s21_set_bit_32(&result->bits[6], 31);
  } else {
    s21_clear_bit_32(&result->bits[6], 31);
  }
  for (int b = 0; b < 6; b++) {
    for (int i = 0; i < 32; i++) {
      if (!over) {
        tmp = s21_get_bit(value_1.bits[b], i) - s21_get_bit(value_2.bits[b], i);
        if (tmp == 1) {
          s21_set_bit_32(&result->bits[b], i);
        } else if (tmp == 0) {
          s21_clear_bit_32(&result->bits[b], i);
        } else if (tmp == -1) {
          if (!s21_find_big_bit(&value_1, i + 32 * b)) {
            s21_set_bit_32(&result->bits[b], i);
          } else {
            over++;
            s21_clear_bit_32(&result->bits[b], i);
            s21_set_bit_32(&result->bits[3], 31);
          }
        }
      } else {
        if (s21_get_bit(value_2.bits[b], i) == 0) {
          s21_clear_bit_32(&result->bits[b], i);
        } else {
          s21_set_bit_32(&result->bits[b], i);
        }
      }
    }
  }
  return 0;
}

int s21_find_big_bit(s21_big_decimal* dec, int index) {
  int res = 1;
  for (int i = index + 1; i < 192 && res; i++) {
    if (s21_get_bit(dec->bits[i / 32], i % 32) == 1) {
      s21_clear_bit_32(&dec->bits[i / 32], i % 32);
      for (int j = i - 1; j >= index; j--) {
        s21_set_bit_32(&dec->bits[j / 32], j % 32);
      }
      res = 0;
    }
  }
  return res;
}

void s21_div_add_bit(s21_big_decimal src, s21_big_decimal* dst, int ind) {
  s21_big_left_shift(dst, 1);
  if (s21_get_bit(src.bits[ind / 32], ind % 32)) {
    s21_set_bit_32(&dst->bits[0], 0);
  }
}

void s21_big_clean(s21_big_decimal* dst) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = 0;
  }
}

int s21_degree_sub(s21_big_decimal* res, unsigned int numb) {
  int result = 0;
  int deg = s21_decimal_degree(res->bits[6]);
  if (deg - (int)numb < 0) {
    result = 1;
  } else {
    s21_big_decimal tmp;
    s21_big_decimal number;
    s21_big_clean(&tmp);
    s21_big_clean(&number);
    tmp.bits[0] = res->bits[6];
    number.bits[0] = numb << 16;
    s21_big_sub(tmp, number, &tmp);
    res->bits[6] = tmp.bits[0];
  }
  return result;
}

int s21_big_to_dec(s21_big_decimal src, s21_decimal* dst) {
  s21_decimal_clean(dst);
  int result = 0;
  int max = s21_find_max(src);
  int degree = s21_decimal_degree(src.bits[6]);
  if (!s21_equal_to_zero(src)) {
    while (((max > 95 && degree > 0) || (degree > 28)) && result == 0 &&
           max != -1) {
      degree--;
      result = s21_bank_round(&src, degree, 0);
      max = s21_find_max(src);
    }
  }
  if (result == 0) {
    if (max > 95) {
      result = 1;
    } else {
      for (int i = 0; i < 4; i++) {
        if (i == 3) {
          dst->bits[i] = src.bits[i + 3];
        } else {
          dst->bits[i] = src.bits[i];
        }
      }
    }
  }
  return result;
}

int s21_bank_round(s21_big_decimal* src, int k, int mod) {
  int result = 0;
  int deg = s21_decimal_degree(src->bits[6]);
  int rest = 0;
  s21_decimal dec_rest = {{0}};
  s21_big_decimal dec_big_rest = {{0}};
  for (int i = 0; i < deg - k; i++) {
    rest = s21_div_by_ten(*src, src, 1);
    s21_degree_sub(src, 1);
    if (rest != -1) {
      s21_from_int_to_decimal(rest, &dec_rest);
      s21_to_big(dec_rest, &dec_big_rest);
      unsigned tmp = src->bits[6];
      s21_big_sub(*src, dec_big_rest, src);
      src->bits[6] = tmp;
      s21_div_by_ten(*src, src, 0);
    } else {
      rest = 0;
    }
  }
  if (deg > 28 && s21_equal_to_zero(*src)) {
    result = 2;
  } else if (mod || (deg - k <= 28 && s21_find_max(*src) < 96 &&
                     s21_find_max(*src) != -1)) {
    int tmp = s21_get_bit(src->bits[0], 0);
    s21_big_decimal one = {{1}};
    if ((tmp && rest >= 5) || (!tmp && rest > 5)) {
      s21_big_add(*src, one, src);
    }
  }
  return result;
}

int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result, int* degree) {
  int res = 0;
  int max = s21_find_max(value_1);
  int flag = max - s21_find_max(value_2);
  int stop = 0;
  int count = 0;
  s21_big_decimal tmp = {{0}};
  s21_big_copy(value_1, &tmp);
  if (flag > 0) {
    s21_big_right_shift(&tmp, flag);
  } else {
    flag = 0;
  }
  while (!stop) {
    int sh = 0;
    s21_add_numbers(value_1, value_2, &tmp, &count, &flag, &sh);
    if (!flag && !s21_equal_to_zero(tmp) && s21_big_is_less(tmp, value_2)) {
      int mult_count = *degree;
      if (*degree < 29) {
        (*degree)++;
        if (sh > 0) {
          s21_big_left_shift(result, sh);
        }
        s21_mult_by_ten(tmp, &tmp);
        s21_big_decimal res_tmp = {{0}};
        s21_big_div(tmp, value_2, &res_tmp, degree);
        for (int i = 0; i < *degree - mult_count; i++) {
          s21_mult_by_ten(*result, result);
        }
        s21_big_add(*result, res_tmp, result);
      }
      stop++;
    } else {
      if (!s21_equal_to_zero(tmp)) {
        sh++;
        s21_big_left_shift(result, sh);
        s21_set_bit_32(&result->bits[0], 0);
        s21_big_sub(tmp, value_2, &tmp);
      } else if (!flag && s21_equal_to_zero(tmp)) {
        if (sh > 0) {
          s21_big_left_shift(result, sh);
        }
        stop++;
      }
    }
  }
  return res;
}

int s21_add_numbers(s21_big_decimal v_1, s21_big_decimal v_2,
                    s21_big_decimal* tmp, int* count, int* flag, int* sh) {
  int res = 0;
  while (s21_big_is_less(*tmp, v_2) && *flag > 0) {
    (*flag)--;
    s21_div_add_bit(v_1, tmp, *flag);
    if (s21_big_is_less(*tmp, v_2) && count != 0) {
      (*sh)++;
    }
  }
  (*count)++;
  return res;
}

int s21_equal_to_zero(s21_big_decimal src) {
  int res = 1;
  for (int i = 0; res && i < 6; i++) {
    if (src.bits[i] != 0) {
      res = 0;
    }
  }
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int res = 0;
  s21_big_decimal v_1 = {{0}};
  s21_big_decimal v_2 = {{0}};
  s21_big_decimal b_res = {{0}};
  s21_to_big(value_1, &v_1);
  s21_to_big(value_2, &v_2);
  if (s21_equal_to_zero(v_2)) {
    s21_decimal_clean(result);
    res = 3;
  } else {
    int degree =
        s21_decimal_degree(v_1.bits[6]) - s21_decimal_degree(v_2.bits[6]);
    s21_big_div(v_1, v_2, &b_res, &degree);
    if (degree < 0) {
      for (int i = 0; i < abs(degree); i++) {
        s21_mult_by_ten(b_res, &b_res);
      }
      degree = 0;
    }
    s21_change_sign(v_1, v_2, &b_res);
    s21_degree_add(&b_res, degree);
    res = s21_big_to_dec(b_res, result);
    if (res == 1 || res == 2) {
      s21_decimal_clean(result);
    }
  }
  return res;
}

void s21_change_sign(s21_big_decimal v_1, s21_big_decimal v_2,
                     s21_big_decimal* res) {
  if ((s21_get_bit(v_1.bits[6], 31) && !s21_get_bit(v_2.bits[6], 31)) ||
      (!s21_get_bit(v_1.bits[6], 31) && s21_get_bit(v_2.bits[6], 31))) {
    s21_set_bit_32(&res->bits[6], 31);
  }
}
