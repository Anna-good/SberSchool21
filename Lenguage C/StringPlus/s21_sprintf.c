#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  s21_parse_format(str, format, &args);
  va_end(args);
  int result = s21_strlen(str);
  return result;
}
// Парсер
void s21_parse_format(char *str, char const *format, va_list *args) {
  int k = 0;
  size_t i = 0;
  for (i = 0; i < s21_strlen(format); i++) {
    if (format[i] == '%') {
      format_struct config = {0};
      i++;
      s21_flags_check(format, &config, &i);
      s21_width_check(format, &config, &i, args);
      s21_precision_check(format, &i, &config, args);
      if ((s21_strchr("hlL", format[i])) != NULL) {
        config.length = format[i];
        i++;
      }
      if ((s21_strchr("cdieEfgGosuxXpn", format[i])) != NULL) {
        config.spec = format[i];
        s21_add_to_str(str, args, &config, &k);
      } else if (format[i] == '%') {
        s21_double_percent_check(str, format, &i, &k);
        i--;
      }
    } else {
      str[k] = format[i];
      k++;
    }
  }
  str[k] = '\0';
}
// Перенаправление взависимости от спецфикатора
void s21_add_to_str(char *str, va_list *args, format_struct *config,
                    int *index) {
  long double numb = 0;
  if (config->spec == 'c') {
    s21_spec_c(str, args, config, index);
  } else if (config->spec == 'o') {
    s21_spec_o(str, args, config, index);
  } else if (config->spec == 'x') {
    s21_spec_x(str, args, config, index, 32);
  } else if (config->spec == 'X') {
    s21_spec_x(str, args, config, index, 0);
  } else if (config->spec == 'n') {
    s21_spec_n(str, args, index);
  } else if (config->spec == 'p') {
    s21_spec_p(str, args, config, index);
  } else if (config->spec == 'u') {
    s21_spec_u(str, args, config, index);
  } else if (config->spec == 's') {
    s21_spec_s(str, args, config, index);
  } else if (config->spec == 'e') {
    if (config->length == 'L') {
      numb = va_arg(*args, long double);
      s21_spec_e(str, numb, config, index, 32);
    } else {
      numb = va_arg(*args, double);
      s21_spec_e(str, numb, config, index, 32);
    }
  } else if (config->spec == 'E') {
    if (config->length == 'L') {
      numb = va_arg(*args, long double);
      s21_spec_e(str, numb, config, index, 0);
    } else {
      numb = va_arg(*args, double);
      s21_spec_e(str, numb, config, index, 0);
    }
  } else if (config->spec == 'i' || config->spec == 'd') {
    s21_spec_d_i(str, args, config, index);
  } else if (config->spec == 'f') {
    if (config->length == 'L') {
      numb = va_arg(*args, long double);
      s21_spec_f(str, numb, config, index);
    } else {
      numb = va_arg(*args, double);
      s21_spec_f(str, numb, config, index);
    }
  } else if (config->spec == 'g') {
    s21_spec_g(str, args, config, index, 32);
  } else if (config->spec == 'G') {
    s21_spec_g(str, args, config, index, 0);
  }
}
// Вещественные числа
void s21_spec_f(char *str, long double num, format_struct *config, int *index) {
  int negative = 0;
  int inf = 0;
  char ch;
  int i = 0;
  char *str_num = calloc(1000, sizeof(char));
  if (!s21_double_overflow_check(str_num, config, num, 32)) {
    inf = 1;
  }
  if (num < 0) {
    negative = 1;
    num *= -1;
  }
  if (!inf) {
    long double int_num = floor(num);
    do {
      ch = fmod(int_num, 10) + 48;
      str_num[i] = ch;
      int_num /= 10;
      i++;
    } while (int_num >= 1);
    s21_string_reverse(str_num);
    int precision = 6;
    if (config->flag_precision) {
      precision = config->precision;
    }
    if (precision != 0 || config->flag_hash != 0) {
      str_num[i] = '.';
      i++;
    }
    s21_add_float(config, str_num, &precision, &i, &num);
  }
  int num_length = s21_strlen(str_num);
  if (negative || config->flag_plus || config->flag_space) {
    num_length++;
  }
  if (config->add_one) {
    num_length++;
  }
  if (!config->flag_minus && !config->flag_zero) {
    s21_fill_width(config->width, num_length, ' ', str, index);
  }
  s21_add_symb(config, &negative, str, index);
  if (config->flag_zero) {
    s21_fill_width(config->width, num_length, '0', str, index);
  }
  if (config->add_one) {
    str[*index] = '1';
    (*index)++;
  }
  str[*index] = '\0';
  s21_strncat(str, str_num, s21_strlen(str_num));
  (*index) += s21_strlen(str_num);
  if (config->flag_minus) {
    s21_fill_width(config->width, num_length, ' ', str, index);
  }
  free(str_num);
}
// Целые числа
void s21_spec_d_i(char *str, va_list *args, format_struct *config, int *index) {
  int dont_add = 0;
  long int num = va_arg(*args, long int);
  if (config->length == 'h') {
    num = (unsigned short int)num;
  } else if (config->length == 'l') {
    num = (unsigned long int)num;
  } else {
    num = (int)num;
  }
  if (num == 0 && config->precision == 0 && config->flag_precision == 1) {
    dont_add = 1;
  }
  if (!dont_add) {
    int negative = 0;
    char *str_num = calloc(100, sizeof(char));
    int i = 0;
    char ch;
    int length;
    if (num < 0) {
      negative = 1;
      num *= -1;
    }
    do {
      ch = num % 10 + 48;
      str_num[i] = ch;
      num /= 10;
      i++;
    } while (num != 0);
    s21_string_reverse(str_num);
    if (!config->precision) {
      length = s21_strlen(str_num);
    } else {
      length = config->precision;
    }
    if (negative || config->flag_plus || config->flag_space) {
      length++;
    }
    if (((!config->flag_minus) && (!config->flag_zero)) ||
        (config->flag_zero && config->precision)) {
      s21_fill_width(config->width, length, ' ', str, index);
    }
    s21_add_symb(config, &negative, str, index);
    if (config->flag_zero && (!config->flag_minus) && (!config->precision)) {
      s21_fill_width(config->width, length, '0', str, index);
    }
    while (config->precision > (int)s21_strlen(str_num)) {
      str[*index] = '0';
      (*index)++;
      config->precision--;
    }
    str[*index] = '\0';
    s21_strncat(str, str_num, s21_strlen(str_num));
    (*index) += s21_strlen(str_num);
    if (config->flag_minus) {
      s21_fill_width(config->width, length, ' ', str, index);
    }
    free(str_num);
  }
}
// Символ
void s21_spec_c(char *str, va_list *args, format_struct *config, int *index) {
  if (config->flag_minus == 1) {
    str[*index] = va_arg(*args, int);
    (*index)++;
  }
  if (config->width > 1) {
    while (config->width != 1) {
      str[*index] = ' ';
      (*index)++;
      config->width--;
    }
  }
  if (config->flag_minus == 0) {
    str[*index] = va_arg(*args, int);
    (*index)++;
  }
}
// Строка
void s21_spec_s(char *str, va_list *args, format_struct *config, int *index) {
  char *var = va_arg(*args, char *);
  int flag = config->flag_precision ? 0 : 1;
  if (config->flag_minus &&
      (!config->flag_precision ||
       (config->flag_precision && config->precision != 0))) {
    for (int i = 0; i < (int)s21_strlen(var) &&
                    (i <= config->precision - 1 || !config->flag_precision);
         i++) {
      str[*index] = var[i];
      (*index)++;
    }
  }
  config->width -= (config->precision + flag * (int)s21_strlen(var));
  for (; config->width > 0; config->width--) {
    str[*index] = ' ';
    (*index)++;
  }
  if (!config->flag_minus &&
      (!config->flag_precision ||
       (config->flag_precision && config->precision != 0))) {
    for (int i = 0; i < (int)s21_strlen(var) &&
                    (i <= config->precision - 1 || !config->flag_precision);
         i++) {
      str[*index] = var[i];
      (*index)++;
    }
  }
}
// Либо вещественная либо научная нотация
void s21_spec_g(char *str, va_list *args, format_struct *config, int *index,
                int flag) {
  if (config->flag_precision && !config->precision) {
    config->precision = 1;
  } else if (!config->flag_precision) {
    config->precision = 6;
    config->flag_precision = 1;
  }
  int count = 0;
  long double numb = 0;
  if (config->length == 'L') {
    numb = va_arg(*args, long double);
  } else {
    numb = va_arg(*args, double);
  }
  long double tmp = numb < 0 ? numb * -1 : numb;
  int over = 0;
  if ((config->length == 'L' && tmp <= LDBL_MAX) ||
      (config->length != 'L' && tmp <= DBL_MAX)) {
    s21_find_e_count(numb, &count, 1);
  } else {
    over = 1;
  }
  if (!over && (count < config->precision || tmp < 1)) {
    config->precision -= count + 1;
    s21_spec_f(str, numb, config, index);
  } else {
    config->precision--;
    s21_spec_e(str, numb, config, index, flag);
  }
}
// Восьмиричная система
void s21_spec_o(char *str, va_list *args, format_struct *config, int *index) {
  char *number =
      s21_working_with_numb(va_arg(*args, unsigned long int), config, 8);
  int value = 32;
  if (!config->only_zero) {
    if (config->flag_zero && !config->precision && !config->flag_minus)
      value = 48;
    if (s21_strlen(number) == 1 && number[0] == '0') {
      config->flag_hash = 0;
    }
    s21_change_config(config, number);
    if (config->flag_minus) {
      s21_add_precision(str, config, index);
      if (config->flag_hash) {
        str[*index] = '0';
        (*index)++;
      }
      str[*index] = '\0';
      s21_strncat(str, number, s21_strlen(number));
      *index += s21_strlen(number);
    }
  }
  if (config->flag_hash && config->only_zero) {
    config->width--;
  }
  if (config->flag_minus && config->only_zero && config->flag_hash) {
    str[*index] = '0';
    (*index)++;
  }
  for (; config->width > 0; (*index)++) {
    str[*index] = value;
    config->width--;
  }
  if (!config->flag_minus && config->only_zero && config->flag_hash) {
    str[*index] = '0';
    (*index)++;
  }
  if (!config->flag_minus && !config->only_zero) {
    s21_add_precision(str, config, index);
    if (config->flag_hash) {
      str[*index] = '0';
      (*index)++;
    }
    str[*index] = '\0';
    s21_strncat(str, number, s21_strlen(number));
    *index += s21_strlen(number);
  }
  free(number);
}
// Беззнаковое целое
void s21_spec_u(char *str, va_list *args, format_struct *config, int *index) {
  config->flag_hash = 0;
  char *number =
      s21_working_with_numb(va_arg(*args, unsigned long int), config, 10);
  int value = 32;
  if (!config->only_zero) {
    if (config->flag_zero && !config->precision && !config->flag_minus) {
      value = 48;
    }
    s21_change_config(config, number);
    if (config->flag_minus) {
      s21_add_precision(str, config, index);
      str[*index] = '\0';
      s21_strncat(str, number, s21_strlen(number));
      *index += s21_strlen(number);
    }
  }
  for (; config->width > 0; (*index)++) {
    str[*index] = value;
    config->width--;
  }
  if (!config->flag_minus && !config->only_zero) {
    s21_add_precision(str, config, index);
    str[*index] = '\0';
    s21_strncat(str, number, s21_strlen(number));
    *index += s21_strlen(number);
  }
  free(number);
}
// Шестнадцатиричная система
void s21_spec_x(char *str, va_list *args, format_struct *config, int *index,
                int flag) {
  int value = 32;
  char *number = s21_convert_to_hex(va_arg(*args, unsigned int), config, flag);
  if (!config->only_zero) {
    if (s21_strlen(number) == 1 && number[0] == '0') {
      config->flag_hash = 0;
    } else if (config->precision != 0 &&
               (int)s21_strlen(number) != config->precision)
      config->precision++;
    if (config->flag_zero && !config->precision && !config->flag_minus) {
      value = 48;
      config->precision = config->width - config->flag_hash;
      config->width = 0;
    }
    s21_change_config(config, number);
    if (config->flag_minus) {
      if (config->flag_hash && (s21_strlen(number) > 1 || number[0] != '0')) {
        str[*index] = '0';
        (*index)++;
        str[*index] = 88 + flag;
        (*index)++;
      }
      s21_add_precision(str, config, index);
      str[*index] = '\0';
      s21_strncat(str, number, s21_strlen(number));
      *index += s21_strlen(number);
    }
    config->width -= config->flag_hash;
  }
  for (; config->width > 0; (*index)++) {
    str[*index] = value;
    config->width--;
  }
  if (!config->flag_minus && !config->only_zero) {
    if (config->flag_hash && s21_strlen(number) > 1 && number[0] != '0') {
      str[*index] = '0';
      (*index)++;
      str[*index] = 88 + flag;
      (*index)++;
    }
    s21_add_precision(str, config, index);
    str[*index] = '\0';
    s21_strncat(str, number, s21_strlen(number));
    *index += s21_strlen(number);
  }
  free(number);
}
// Запись по адресу количества записанных символов до спецификатора n
void s21_spec_n(char *str, va_list *args, int *index) {
  int *res = (va_arg(*args, int *));
  str[*index] = '\0';
  *res = s21_strlen(str);
}
// Записывает адресс в шетснадцатиричной система
void s21_spec_p(char *str, va_list *args, format_struct *config, int *index) {
  int value = 32;
  config->flag_hash = 2;
  if (config->precision != 0) {
    config->precision += 2;
  }
  if (!config->flag_minus && !config->precision && config->flag_zero) {
    value = 48;
    config->precision = config->width;
    config->width = 0;
  }
  char *number = s21_convert_pointer_address(va_arg(*args, void *));
  s21_change_config(config, number);
  if (config->flag_minus) {
    str[*index] = '0';
    (*index)++;
    str[*index] = 88 + 32;
    (*index)++;
    s21_add_precision(str, config, index);
    str[*index] = '\0';
    s21_strncat(str, number, s21_strlen(number));
    *index += s21_strlen(number);
  }
  s21_strlen(number);
  for (; config->width > 0; (*index)++) {
    str[*index] = value;
    config->width--;
  }
  if (!config->flag_minus) {
    str[*index] = '0';
    (*index)++;
    str[*index] = 88 + 32;
    (*index)++;
    s21_add_precision(str, config, index);
    str[*index] = '\0';
    s21_strncat(str, number, s21_strlen(number));
    *index += s21_strlen(number);
  }
  free(number);
}
// Научная запись числа
void s21_spec_e(char *str, long double number, format_struct *config,
                int *index, int flag) {
  char *numb;
  char sign = '\0';
  if (config->flag_minus) {
    config->flag_zero = 0;
  }
  numb = s21_exp_convert(config, number, flag, &sign);
  config->width -= (int)s21_strlen(numb);
  if (!config->flag_minus) {
    s21_exp_no_minus_add_width(str, numb, index, config, sign);
  } else {
    s21_exp_minus_add_width(str, numb, index, config, sign);
  }
  free(numb);
}
// Проверка на %%
void s21_double_percent_check(char *str, const char *format, size_t *format_ind,
                              int *str_ind) {
  do {
    str[*str_ind] = format[*format_ind];
    (*format_ind)++;
    (*str_ind)++;
  } while (format[*format_ind] != '%' && *format_ind < s21_strlen(format));
}
// Заполнение структуры при наличии флагов
void s21_flags_check(char const *format, format_struct *config, size_t *i) {
  while ((s21_strchr("-+#0 ", format[*i])) != NULL) {
    if (format[*i] == '-') config->flag_minus = 1;
    if (format[*i] == '+') config->flag_plus = 1;
    if (format[*i] == ' ') config->flag_space = 1;
    if (format[*i] == '0') config->flag_zero = 1;
    if (format[*i] == '#') config->flag_hash = 1;
    (*i)++;
  }
}
// Проверка ширины
void s21_width_check(char const *format, format_struct *config, size_t *i,
                     va_list *args) {
  if ((format[*i] >= '0' && format[*i] <= '9') || format[*i] == '*') {
    if (format[*i] == '*') {
      config->width = va_arg(*args, int);
      (*i)++;
    } else {
      int width = (int)format[*i] - 48;
      (*i)++;
      while (format[*i] >= '0' && format[*i] <= '9') {
        width = width * 10 + (int)format[*i] - 48;
        (*i)++;
      }
      config->width = width;
    }
  }
}
// Проверка точности
void s21_precision_check(const char *format, size_t *i, format_struct *config,
                         va_list *args) {
  if (format[*i] == '.') {
    (*i)++;
    config->flag_precision = 1;
    if (format[*i] == '*') {
      config->precision = va_arg(*args, int);
      (*i)++;
    } else if (format[*i] >= '0' && format[*i] <= '9') {
      int precision = (int)format[*i] - 48;
      (*i)++;
      while (format[*i] >= '0' && format[*i] <= '9') {
        precision = precision * 10 + (int)format[*i] - 48;
        (*i)++;
      }
      config->precision = precision;
    }
  }
}
// Функция для работы с целыми числами (u, x, o)
char *s21_working_with_numb(unsigned long int numb, format_struct *config,
                            int divisor) {
  if (config->length == 'h') {
    numb = (unsigned short)numb;
  } else if (config->length != 'l') {
    numb = (unsigned int)numb;
  }
  int k = 0;
  char *result = calloc(100, sizeof(char));
  if (!s21_check_zero_int(numb, config) ||
      (config->flag_hash && config->spec == 'o')) {
    do {
      result[k] = numb % divisor + 48;
      k++;
      numb /= divisor;
    } while (numb != 0);
    result[k] = '\0';
    s21_string_reverse(result);
  }
  return result;
}
// Перевод числа в 16-ную систему
char *s21_convert_to_hex(unsigned long int num, format_struct *config,
                         int flag) {
  char *result = calloc(1000, sizeof(char));
  int count = 0;
  int tmp = 0;
  if (config->length == 'h') {
    num = (unsigned short int)num;
  } else if (config->length != 'l') {
    num = (unsigned int)num;
  }
  if (!s21_check_zero_int(num, config)) {
    do {
      tmp = num % 16;
      num /= 16;
      if (tmp < 10) {
        result[count] = tmp + 48;
      } else {
        result[count] = tmp % 10 + 65 + flag;
      }
      count++;
    } while (num != 0);
  }
  result[count] = '\0';
  s21_string_reverse(result);
  return result;
}
// Перевод адресса в 16-ную систему
char *s21_convert_pointer_address(void *pointer) {
  char *result = calloc(100, sizeof(char));
  unsigned long int a = (unsigned long)pointer;
  int count = 0;
  int tmp = 0;
  do {
    tmp = a % 16;
    a /= 16;
    if (tmp < 10) {
      result[count] = tmp + 48;
    } else {
      result[count] = tmp % 10 + 65 + 32;
    }
    count++;
  } while (a != 0);
  result[count] = '\0';
  s21_string_reverse(result);
  return result;
}
// Перевернуть строку
void s21_string_reverse(char *str) {
  int length = s21_strlen(str);
  char tmp;
  for (int i = 0; i < length / 2; i++) {
    tmp = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = tmp;
  }
}
// Изменение ширины и точности
void s21_change_config(format_struct *config, char *str) {
  int length = 0;
  config->precision -= config->flag_hash;
  if ((int)s21_strlen(str) >= config->precision) {
    length = s21_strlen(str);
    config->precision = 0;
  } else {
    length = config->precision;
    config->precision -= (int)s21_strlen(str);
  }
  config->width = config->width - config->flag_hash - length;
}
// Добавление точности в виде нулей
void s21_add_precision(char *str, format_struct *config, int *index) {
  for (; config->precision > 0; (*index)++) {
    str[*index] = '0';
    config->precision--;
  }
}
// Проверка переполнения переменных типа double
int s21_double_overflow_check(char *str, format_struct *config,
                              long double number, int change) {
  int flag = 1;
  number *= number >= 0 ? 1 : -1;
  if (config->length == 'L') {
    if (number > LDBL_MAX || number < LDBL_MIN) {
      str[0] = 73 + change;
      str[1] = 78 + change;
      str[2] = 70 + change;
      str[3] = '\0';
      flag = 0;
      config->flag_zero = 0;
    }
  } else if (number > DBL_MAX || number < DBL_MIN) {
    str[0] = 73 + change;
    str[1] = 78 + change;
    str[2] = 70 + change;
    str[3] = '\0';
    flag = 0;
    config->flag_zero = 0;
  }
  return flag;
}
// Проверка необходимости знака
char s21_sign_check(long double numb, format_struct *config) {
  char res = '\0';
  if (numb < 0) {
    res = '-';
  } else if (config->flag_space) {
    res = ' ';
  } else if (config->flag_plus) {
    res = '+';
  }
  return res;
}
// Перевод в научную нотацию
char *s21_exp_convert(format_struct *config, long double numb, int change,
                      char *n_sign) {
  char *res = calloc(600, sizeof(char));
  int e_count = 0;
  char e_sign = '\0';
  *n_sign = s21_sign_check(numb, config);
  long double tmp = numb >= 0 ? numb : numb * -1;
  config->precision += !config->flag_precision ? 6 : 0;
  if (!s21_zero_check(res, config, numb, change) &&
      s21_double_overflow_check(res, config, numb, change)) {
    if (tmp < 1) {
      s21_find_e_count(numb, &e_count, 0);
      numb *= pow(10, e_count);
      e_sign = '-';
    } else {
      s21_find_e_count(numb, &e_count, 1);
      numb /= pow(10, e_count);
      e_sign = '+';
    }
    s21_convert_to_scientific(res, config, numb, &e_count);
    s21_add_exp_tail(res, e_sign, e_count, change);
  }
  return res;
}
// Находим степень экспоненты
void s21_find_e_count(long double numb, int *count, int kod) {
  numb *= numb >= 0 ? 1 : -1;
  if (!kod) {
    while (numb < 1) {
      numb *= 10;
      (*count)++;
    }
  } else {
    long double tmp = floor(numb);
    while (tmp / 10 >= 1) {
      tmp /= 10;
      (*count)++;
    }
  }
}
// Проверка, если число равно 0
int s21_zero_check(char *res, format_struct *config, long double numb,
                   int change) {
  int flag = 0;
  int index;
  if (numb == 0) {
    flag = 1;
    res[0] = '0';
    res[1] = '.';
    for (index = 2; index < config->precision + 2; index++) {
      res[index] = '0';
    }
    res[index] = 69 + change;
    index++;
    res[index] = '+';
    index++;
    res[index] = '0';
    index++;
    res[index] = '0';
  }
  return flag;
}
// Работа с числом
void s21_convert_to_scientific(char *res, format_struct *config,
                               long double numb, int *e) {
  numb *= numb >= 0 ? 1 : -1;
  long double tmp = 0;
  int length = config->precision + 2;
  int fix = 0;
  int power = 0;
  for (int i = 0; i < length; i++) {
    if (i != 1) {
      tmp = floor(numb * pow(10, power)) - tmp * 10;
      res[i] = (int)tmp + 48;
      if (i == length - 1 || length == 2) {
        tmp = floor(numb * pow(10, power));
        tmp = floor(numb * pow(10, power + 1)) - tmp * 10;
        if (tmp >= 5) {
          if (res[i] + 1 > '9') {
            fix = 1;
          } else {
            res[i]++;
          }
        }
      }
      tmp = floor(numb * pow(10, power));
      power++;
    } else if (length > 2 || config->flag_hash) {
      res[i] = '.';
    }
  }
  res[length] = '\0';
  if (fix) {
    s21_round_fix(res, length, e);
  }
  s21_non_significant_zeros(res, config);
}
// Округление
void s21_round_fix(char *numb, int length, int *e) {
  int change = 1;
  for (int i = length - 1; i >= 0 && change; i--) {
    if (numb[i] == '.' || (length == 2 && i == 1)) {
      continue;
    }
    numb[i]++;
    if (numb[i] > '9') {
      numb[i] = '0';
      change = 1;
      if (i == 0 && change) {
        numb[i] = '1';
        (*e)++;
      }
    } else {
      change = 0;
    }
  }
}
// Добавляем хвостик при научной нотации
void s21_add_exp_tail(char *numb, char sign, int e, int change) {
  int length = s21_strlen(numb);
  numb[length] = 69 + change;
  length++;
  numb[length] = sign;
  length++;
  for (int i = 1; i >= 0; i--) {
    numb[length + i] = e % 10 + 48;
    e /= 10;
  }
  numb[length + 2] = '\0';
}
// Ширина если нет флага -
void s21_exp_no_minus_add_width(char *str, char *numb, int *index,
                                format_struct *config, char sign) {
  int change = 32;
  config->width -= sign != '\0' ? 1 : 0;
  if (config->flag_zero) {
    change = 48;
    if (sign != '\0') {
      str[*index] = sign;
      (*index)++;
    }
  }
  for (; config->width > 0; config->width--) {
    str[*index] = change;
    (*index)++;
  }
  if (!config->flag_zero) {
    if (sign != '\0') {
      str[*index] = sign;
      (*index)++;
    }
  }
  str[*index] = '\0';
  s21_strncat(str, numb, s21_strlen(numb));
  *(index) += (int)s21_strlen(numb);
}
// Ширина если есть флаг -
void s21_exp_minus_add_width(char *str, char *numb, int *index,
                             format_struct *config, char sign) {
  if (sign != '\0') {
    str[*index] = sign;
    (*index)++;
    config->width--;
  }
  str[*index] = '\0';
  s21_strncat(str, numb, s21_strlen(numb));
  (*index) += (int)s21_strlen(numb);
  for (; config->width > 0; config->width--) {
    str[*index] = ' ';
    (*index)++;
  }
}
// Вывод только 0
int s21_check_zero_int(unsigned long int numb, format_struct *config) {
  int flag = 0;
  if (numb == 0 && config->flag_precision && config->precision == 0) {
    flag = 1;
    config->only_zero++;
  }
  return flag;
}
// Добавление знака
void s21_add_symb(format_struct *config, int *negative, char *str, int *index) {
  if (*negative) {
    str[*index] = '-';
    (*index)++;
  } else if (config->flag_plus) {
    str[*index] = '+';
    (*index)++;
  } else if (config->flag_space) {
    str[*index] = ' ';
    (*index)++;
  }
}
// Заполнение ширины
void s21_fill_width(int width, int length, int value, char *str, int *index) {
  while (width > length) {
    str[*index] = value;
    (*index)++;
    width--;
  }
}
// Добавление части после точки + округление
void s21_add_float(format_struct *config, char *str_num, int *precision, int *i,
                   long double *num) {
  long double int_num;
  char ch;
  int increase = 0;
  (*num) -= floor(*num);
  for (int k = 0; k < (*precision) + 1; k++) {
    (*num) *= 10;
    int_num = floor(*num);
    ch = int_num + 48;
    if (k == (*precision)) {
      if (ch >= '5' && ch <= '9') {
        increase = 1;
      }
    } else {
      str_num[*i] = ch;
      (*i)++;
      (*num) -= int_num;
    }
  }
  for (int k = (s21_strlen(str_num) - 1); k >= 0 && increase; k--) {
    if (str_num[k] == '.') {
      continue;
    }
    str_num[k]++;
    if (str_num[k] > '9') {
      str_num[k] = '0';
      if (k == 0) {
        config->add_one = 1;
      }
    } else {
      increase = 0;
    }
  }
}
// Убираем незначащие нули для g
void s21_non_significant_zeros(char *str, format_struct *config) {
  if (config->spec == 'g' || config->spec == 'G') {
    int length = s21_strlen(str);
    int flag = 1;
    for (int i = length - 1; flag && i > 0; i--) {
      if (str[i] == '0' || (str[i] == '.' && !config->flag_hash)) {
        str[i] = '\0';
      } else {
        flag = 0;
      }
    }
  }
}
