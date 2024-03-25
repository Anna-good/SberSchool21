#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_INT_MAX 2147483647
#define S21_INT_MIN -2147483648

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

// Работа с одним битом
int s21_get_bit(unsigned int x, unsigned int index);
int s21_set_bit_32(unsigned int* x, unsigned index);
int s21_clear_bit_32(unsigned int* x, unsigned index);

// Конвертация
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_negate(s21_decimal value, s21_decimal* result);

// Арифметика
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// Доп функции для обычного децимал
void s21_decimal_clean(s21_decimal* dec);

// Работа со степенью десятки
int s21_degree_sub(s21_big_decimal* res, unsigned int numb);
int s21_decimal_degree(unsigned int dec);
int s21_degree_add(s21_big_decimal* dec, unsigned int num);

// Вспомогательные функции
void s21_add_32(unsigned int value_1, unsigned int value_2,
                unsigned int* result, int* change);
int s21_dec_last_bit_zero_check(s21_decimal dec);
void s21_from_str_to_decimal(char str, s21_big_decimal* dst, int c);

// Операторы сравнения
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_less_32(unsigned int a, unsigned int b);
int s21_big_is_less(s21_big_decimal a, s21_big_decimal b);

// Округления
int s21_bank_round(s21_big_decimal* src, int k, int mod);
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_for_rounding(s21_decimal value, s21_decimal* result, int floor,
                     int round);

// big decimal
void s21_big_copy(s21_big_decimal src, s21_big_decimal* dst);
int s21_big_left_shift(s21_big_decimal* res, int k);
void s21_big_right_shift(s21_big_decimal* res, int k);
int s21_mult_by_ten(s21_big_decimal value, s21_big_decimal* res);
int s21_dec_equalize(s21_big_decimal* res_1, s21_big_decimal* res_2);
int s21_to_big(s21_decimal dec, s21_big_decimal* res);
int s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result);
int s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result);
int s21_find_big_bit(s21_big_decimal* dec, int index);
void s21_div_add_bit(s21_big_decimal src, s21_big_decimal* dst, int ind);
int s21_div_by_ten(s21_big_decimal value, s21_big_decimal* res, int mode);
void s21_big_clean(s21_big_decimal* dst);
int s21_big_to_dec(s21_big_decimal src, s21_decimal* dst);
int s21_add_numbers(s21_big_decimal v_1, s21_big_decimal v_2,
                    s21_big_decimal* tmp, int* count, int* flag, int* sh);
int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result, int* degree);
int s21_equal_to_zero(s21_big_decimal src);
void s21_change_sign(s21_big_decimal v_1, s21_big_decimal v_2,
                     s21_big_decimal* res);

#endif
