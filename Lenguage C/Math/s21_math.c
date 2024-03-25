#include "s21_math.h"

// Модуль целочисленный
int s21_abs(int x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}
// Округление вверх
long double s21_ceil(double x) {
  if (x - (int)x > 0) {
    x = (int)x + 1;
  } else if (x - (int)x < 0) {
    x = (int)x;
  }
  return x;
}
// Значение числа по модулю
long double s21_fabs(double x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}
// Округление к нулю
long double s21_floor(double x) {
  if (x < 0 && x - (int)x != 0)
    x = (int)x - 1;
  else if (x >= 0 && x - (int)x != 0)
    x -= x - (int)x;
  return x;
}
// Деление с остатком вещественных чисел
long double s21_fmod(double x, double y) {
  int token_x = x < 0 ? -1 : 1;
  long double res = 0;
  if (check_value(&res, x) && check_value(&res, y)) {
    x *= token_x;
    y *= y < 0 ? -1 : 1;
    if (y != 0) {
      while (x - y >= 0) {
        x -= y;
      }
      res = x * token_x;
    } else {
      res = S21_NAN;
    }
  }
  return res;
}
// Извлечение корня
long double s21_sqrt(double x) {
  long double res = 0;
  if (check_value(&res, x)) {
    long double change = 1;
    int count = 0;
    if (x >= 0) {
      while (res * res != x && count <= 8) {
        if (res * res > x) {
          res -= change;
          change /= 10;
          count++;
        }
        res += count <= 8 ? change : 0;
      }
    } else {
      res = S21_NAN;
    }
  }
  return res;
}
// Расчет экспоненты через ряд Тейлора
long double s21_exp(double x) {
  long double res = 1;
  if (check_value(&res, x)) {
    if (x != 0) {
      long double tmp = 1;
      long double i = 1;
      int flag = 1;
      while (s21_fabs(tmp) > epsilone && flag) {
        tmp *= x / i;
        i++;
        res += tmp;
        if (res > DBL_MAX) {
          res = S21_INF_NEG;
          flag = 0;
        }
      }
    }
  }
  return res;
}
// Расчет натурального log с основанием e при помощи метода Галея
long double s21_log(double x) {
  long double res = 0;
  if (check_value(&res, x)) {
    if (x == 0) {
      res = S21_INF_NEG;
    } else if (x < 0) {
      res = S21_NAN;
    } else if (x == 1) {
      res = 0;
    } else {
      int whole_count = 0;
      long double curent = 0;
      for (; x >= S21_E; whole_count++, x /= S21_E) continue;
      for (int i = 0; i < 100; i++) {
        curent = res;
        res += 2 * ((x - s21_exp(curent)) / (x + s21_exp(curent)));
      }
      res += whole_count;
    }
  }
  return res;
}
// Возведение в степень
long double s21_pow(double base, double exp) {
  long double res = 0;
  if (check_value(&res, base) && check_value(&res, exp)) {
    if (exp == 0) {
      res = 1;
    } else if (base != 0) {
      res = 1;
      long double old_exp = exp;
      long double log_base = base;
      log_base *= base < 0 ? -1 : 1;
      while (exp >= 1) {
        res *= log_base;
        exp--;
      }
      if (exp != 0) {
        res *= s21_exp(exp * s21_log(log_base));
      }
      res *= base < 0 && s21_fmod(old_exp, 2.0) != 0 ? -1 : 1;
    }
  }
  return res;
}
// Рассчет синуса через ряд Тейлора
long double s21_sin(double x) {
  long double tmp = 1;
  long double res = 0;
  if (check_value(&res, x)) {
    long double fact = 1;
    int i = 1;
    int power = 0;
    x = s21_fmod(x, 2 * S21_M_PI);
    while (s21_fabs(tmp) > epsilone && power < 100) {
      tmp = s21_pow(x, power * 2 + 1) / fact;
      res += power % 2 != 0 ? -tmp : tmp;
      power++;
      facorial_step(&fact, &i);
    }
  }
  return res;
}
// Косинус также через ряд Тейлора
long double s21_cos(double x) {
  long double tmp = 1;
  long double res = 0;
  if (check_value(&res, x)) {
    long double fact = 1;
    int i = 0;
    int power = 0;
    x = s21_fmod(x, 2 * S21_M_PI);
    while (s21_fabs(tmp) > epsilone && power < 100) {
      tmp = s21_pow(x, power * 2) / fact;
      res += power % 2 != 0 ? -tmp : tmp;
      power++;
      facorial_step(&fact, &i);
    }
  }
  return res;
}
// Расчет значения факториала с шагом на два
void facorial_step(long double* cur_fact, int* step) {
  for (int i = 0; i < 2; i++) {
    (*step)++;
    (*cur_fact) *= *step;
  }
}
// Тангенс (КРАЕВЫЕ!)
long double s21_tan(double x) {
  long double res = 0;
  if (check_value(&res, x)) {
    res = s21_cos(x);
    if (res != 0) {
      res = s21_sin(x) / res;
    } else {
      res = S21_NAN;
    }
  }
  return res;
}
// Арксинус через ряд Тейлора
long double s21_asin(double x) {
  long double res = 0;
  if (check_value(&res, x)) {
    if (s21_fabs(x) < 1) {
      long double fact1 = 1;
      long double fact2 = 1;
      long double i = 1;
      long double tmp = 1;
      res = x;
      while (s21_fabs(tmp) >= epsilone) {
        tmp = (fact1 * s21_pow(x, 2 * i + 1)) / (fact2 * (2 * i) * (2 * i + 1));
        res += tmp;
        fact2 *= 2 * i;
        i++;
        fact1 *= 2 * i - 1;
      }
    } else if (s21_fabs(x) == 1) {
      res = S21_M_PI / (2 * x);
    } else {
      res = S21_NAN;
    }
  }
  return res;
}
// Арккосинус через ряд Тейлора (Посмотреть еще края)
long double s21_acos(double x) {
  long double res = 0;
  if (check_value(&res, x)) {
    if (s21_fabs(x) < 1) {
      res = S21_M_PI / 2.0 - s21_asin(x);
    } else if (x == -1) {
      res = S21_M_PI;
    } else if (x == 1) {
      res = 0;
    } else {
      res = S21_NAN;
    }
  }
  return res;
}
// Арктангенс через ряд Тейлора
long double s21_atan(double x) {
  long double res = 0;
  if (check_value(&res, x)) {
    long double tmp = 1;
    long double i = 1;
    int token = -1;
    if (s21_fabs(x) == 1) {
      res = S21_M_PI / 4.0 * x;
    } else {
      if (s21_fabs(x) < 1) {
        token = 1;
      }
      while (s21_fabs(tmp) >= epsilone && i < 5000) {
        tmp = s21_pow(x, 2 * i * token - 1 * token) / (2 * i - 1);
        tmp *= s21_fmod(i, 2) == 0 ? -1 : 1;
        res += tmp;
        i++;
      }
      if (s21_fabs(x) > 1) {
        res = (S21_M_PI * s21_sqrt(x * x)) / (2 * x) - res;
      }
    }
  }
  return res;
}

int check_value(long double* res, double x) {
  int flag = 0;
  if (x == S21_NAN) {
    *res = S21_NAN;
  } else if (x == S21_INF_NEG) {
    *res = S21_INF_NEG;
  } else if (x == S21_INF_POS) {
    *res = S21_INF_POS;
  } else {
    flag = 1;
  }
  return flag;
}
