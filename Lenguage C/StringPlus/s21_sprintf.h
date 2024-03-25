#ifndef S21_SPRINTF_H

#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#define S21_SPRINTF_H

typedef struct {
  int width;
  char length;
  int precision;
  char spec;
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_zero;
  int flag_hash;
  int flag_precision;
  int add_one;
  int only_zero;
} format_struct;

int s21_sprintf(char *str, const char *format, ...);
void s21_parse_format(char *str, char const *format, va_list *args);
void s21_add_to_str(char *str, va_list *args, format_struct *config,
                    int *index);
void s21_double_percent_check(char *str, const char *format, size_t *format_ind,
                              int *str_ind);
void s21_flags_check(char const *format, format_struct *config, size_t *i);
void s21_width_check(char const *format, format_struct *config, size_t *i,
                     va_list *args);

char *s21_working_with_numb(unsigned long int numb, format_struct *config,
                            int divisor);
void s21_convert_to_string(unsigned long long int numb, char *str, int length);
void s21_precision_check(const char *format, size_t *i, format_struct *config,
                         va_list *args);

char *s21_convert_to_hex(unsigned long int num, format_struct *config,
                         int flag);
void s21_string_reverse(char *str);

char *s21_convert_pointer_address(void *pointer);

char *s21_exp_convert(format_struct *config, long double numb, int change,
                      char *n_sign);
int s21_double_overflow_check(char *str, format_struct *config,
                              long double number, int change);
void s21_find_e_count(long double numb, int *count, int kod);
int s21_zero_check(char *res, format_struct *config, long double numb,
                   int change);
char s21_sign_check(long double numb, format_struct *config);
void s21_exp_no_minus_add_width(char *str, char *numb, int *index,
                                format_struct *config, char sign);
void s21_exp_minus_add_width(char *str, char *numb, int *index,
                             format_struct *config, char sign);

void s21_convert_to_scientific(char *res, format_struct *config,
                               long double numb, int *e);
void s21_round_fix(char *numb, int length, int *e);
void s21_add_exp_tail(char *numb, char sign, int e, int change);
void s21_add_float(format_struct *config, char *str_num, int *precision, int *i,
                   long double *num);
void s21_fill_width(int width, int length, int value, char *str, int *index);
void s21_add_symb(format_struct *config, int *negative, char *str, int *index);

void s21_spec_c(char *str, va_list *args, format_struct *config, int *index);
void s21_spec_d_i(char *str, va_list *args, format_struct *config, int *index);
void s21_spec_f(char *str, long double numb, format_struct *config, int *index);
void s21_spec_o(char *str, va_list *args, format_struct *config, int *index);
void s21_spec_u(char *str, va_list *args, format_struct *config, int *index);
void s21_spec_x(char *str, va_list *args, format_struct *config, int *index,
                int flag);
void s21_spec_n(char *str, va_list *args, int *index);
void s21_spec_p(char *str, va_list *args, format_struct *config, int *index);
void s21_spec_s(char *str, va_list *args, format_struct *config, int *index);
void s21_spec_e(char *str, long double number, format_struct *config,
                int *index, int flag);
void s21_spec_g(char *str, va_list *args, format_struct *config, int *index,
                int flag);
void s21_non_significant_zeros(char *str, format_struct *config);

void s21_change_config(format_struct *config, char *str);
void s21_add_precision(char *str, format_struct *config, int *index);

int s21_check_zero_int(unsigned long int numb, format_struct *config);
#endif
