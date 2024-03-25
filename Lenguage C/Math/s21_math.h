#ifndef S21_MATH_H
#define S21_MATH_H
#include <float.h>
#include <stdio.h>

#define S21_NAN 0.0 / 0.0
#define S21_INF_POS 1.0 / 0.0
#define S21_INF_NEG -1.0 / 0.0

#define epsilone 0.0000000001

#define S21_E 2.7182818284
#define S21_M_PI 3.1415926535

int s21_abs(int x);
long double s21_fabs(double x);

long double s21_ceil(double x);
long double s21_floor(double x);

long double s21_fmod(double x, double y);
long double s21_sqrt(double x);

long double s21_exp(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);

long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);

long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);

void facorial_step(long double* cur_fact, int* step);

int check_value(long double* res, double x);

#endif
