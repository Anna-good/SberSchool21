#include "s21_string.h"

#ifdef __APPLE__
#define MAX_ERR 107
#define head "Unknown error: "
#define errors                                                                 \
  {                                                                            \
    "Undefined error: 0", "Operation not permitted",                           \
        "No such file or directory", "No such process",                        \
        "Interrupted system call", "Input/output error",                       \
        "Device not configured", "Argument list too long",                     \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Resource busy", "File exists", "Cross-device link",                   \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disc quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable (or shared library)", "Bad CPU type in executable",    \
        "Shared library version mismatch", "Malformed Mach-o file",            \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "EMULTIHOP (Reserved)",          \
        "No message available on STREAM", "ENOLINK (Reserved)",                \
        "No STREAM resources", "Not a STREAM", "Protocol error",               \
        "STREAM ioctl timeout", "Operation not supported on socket",           \
        "Policy not found", "State not recoverable", "Previous owner died",    \
        "Interface output queue is full"                                       \
  }
#endif

#ifdef __linux__
#define MAX_ERR 134
#define head "Unknown error "
#define errors                                                                 \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#endif
//  Возвращает новую строку, в которой удаляются все начальные и
//  конечные вхождения набора заданных символов (trim_chars) из данной строки
void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    int len_src = s21_strlen(src);
    int len_trim = s21_strlen(trim_chars);
    int index1 = 0;
    int index2 = len_src - 1;  // длина без \0
    int fbreak = 1;
    int first_char = 0;
    int last_char = 0;
    // проходим от начала строки и находим индекс последнего совпадающего
    // элемента от начала
    for (int i = 0; i <= len_src && fbreak; i++) {
      fbreak = 0;
      for (int k = 0; k < len_trim; k++) {
        if (src[i] == trim_chars[k]) {
          index1 = i;
          fbreak = 1;
          first_char = 1;  // если первый символ был
        }
      }
    }
    // проходим от конца строки и находим индекс первого совпадающего элемента с
    // конца
    fbreak = 1;
    for (int i = (len_src - 1); i > index1 && fbreak; i--) {
      fbreak = 0;
      for (int k = 0; k < len_trim; k++) {
        if (src[i] == trim_chars[k]) {
          index2 = i;
          fbreak = 1;
          last_char = 1;  // если последний символ был
        }
      }
    }
    // index1 - перед первым нужным, index2 - после первого нужного
    if (first_char) {
      index1++;  //- первый нужный
    }
    if (last_char) {
      index2--;  //- второй нужный
    }
    if (!first_char && !last_char) {  // и в начале и в конце не было совпадений
                                      // = копируем полностью
      res = calloc(len_src + 1, sizeof(char));
      res[0] = '\0';
      s21_strncpy(res, src, len_src);
    } else {
      if (index2 - index1 <= 0) {  // нужно удалить всю строку (??)
        res = (char *)malloc(1);
        res[0] = '\0';
      } else {
        res = calloc(index2 - index1 + 2, sizeof(char));
        s21_strncpy(res, src + index1, index2 - index1 + 1);
        res[index2 - index1 + 1] = '\0';
      }
    }
  }
  return res;
}

//  возвращает копию src в которую вставлена str
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res;
  if (str == S21_NULL || src == S21_NULL) {
    res = S21_NULL;
  } else {
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_str = s21_strlen(str);
    s21_size_t len = len_src + len_str;
    res = (char *)malloc(len + 1);
    for (s21_size_t i = 0; i < len; i++) {
      if (i == start_index) {
        for (s21_size_t k = 0; k < len_str; k++, i++) {
          res[i] = str[k];
        }
      }
      if (i < start_index) {
        res[i] = src[i];
      }
      if (i > start_index) {
        res[i] = src[i - len_str];
      }
    }
    res[len] = '\0';
  }
  return res;
}

// //все буквы в нижний регистр
void *s21_to_lower(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *res = (char *)malloc(len + 1);

  if (str == S21_NULL) {
    res = S21_NULL;
  } else {
    for (s21_size_t i = 0; i <= len; i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        res[i] = str[i] + 32;
      } else {
        res[i] = str[i];
      }
    }
  }
  return res;
}

//  все буквы в верхний регистр
void *s21_to_upper(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *res = (char *)malloc(len + 1);

  if (str == S21_NULL) {
    res = S21_NULL;
  } else {
    for (s21_size_t i = 0; i <= len; i++) {
      if (str[i] >= 97 && str[i] <= 123) {
        res[i] = str[i] - 32;
      } else {
        res[i] = str[i];
      }
    }
  }
  return res;
}

// нужно вписать номер ошибки в строку
char *s21_strerror(int errnum) {
  char *er_list[MAX_ERR] = errors;
  static char res[1000];
  for (s21_size_t i = 0; i < 1000; i++) {
    res[i] = '\0';
  }
  if (errnum >= 0 && errnum <= MAX_ERR) {
    s21_strncpy(res, er_list[errnum], s21_strlen(er_list[errnum]));
  } else {
    char u_error[1000];
    s21_convert_error_to_numb(u_error, errnum);
    s21_strncpy(res, u_error, s21_strlen(u_error));
  }
  return res;
}

void s21_convert_error_to_numb(char *res, int errnum) {
  s21_size_t count = 0;
  for (count = 0; count < s21_strlen(head); count++) {
    res[count] = head[count];
  }
  if (errnum < 0) {
    res[count] = '-';
    count++;
    errnum = abs(errnum);
  }
  int start = count;
  do {
    res[count] = errnum % 10 + 48;
    errnum /= 10;
    count++;
  } while (errnum > 0);
  int final = count;
  for (int i = 0; i < (final - start) / 2; i++) {
    char tmp = res[start + i];
    res[start + i] = res[final - 1 - i];
    res[final - 1 - i] = tmp;
  }
  res[count] = '\0';
}
// ищет первое вхождение второй строки в первую
char *s21_strstr(const char *haystack, const char *needle) {
  const char *res = S21_NULL;
  int match = 1;

  for (s21_size_t i = 0; i < s21_strlen(haystack); i++) {
    for (s21_size_t k = 0; k < s21_strlen(needle); k++) {
      if (haystack[k + i] != needle[k]) {
        match = 0;
      }
    }
    if (match) {
      res = haystack + i;
      break;
    }
    match = 1;
  }
  return (char *)res;
}

// последнее вхождение символа в строке
char *s21_strrchr(const char *str, int c) {
  char const *res = S21_NULL;
  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      res = str + i;
    }
  }
  return (char *)res;
}

// ищет первое вхождение любого символа из str2 в str1 и возвращает указатель на
// совпавшй элемент
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *res = S21_NULL;
  int got = 0;

  for (s21_size_t i = 0; i <= s21_strlen(str1); i++) {
    for (s21_size_t k = 0; k <= s21_strlen(str2); k++) {
      if (str1[i] == str2[k]) {
        if (!got) {
          res = str1 + i;
          got = 1;
        }
      }
    }
  }
  return (char *)res;
}

// ищет первое вхождение любого символа из str2 в str1 и возвращает номер
// элемента который совпал Вычисляет длину начального сегмента str1, который
// полностью состоит из символов, не входящих в str2 (по тз)
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res;
  int got = 0;

  for (s21_size_t i = 0; i <= s21_strlen(str1); i++) {
    for (s21_size_t k = 0; k <= s21_strlen(str2); k++) {
      if (str1[i] == str2[k]) {
        if (!got) {
          res = i;
          got = 1;
        }
      }
    }
  }
  return res;
}

// копирует из src в dest n символов и если массив короче чем n, заменяет
// оставшися символы '\0'
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int len = s21_strlen(src);
  s21_size_t i;

  for (i = 0; i < n && len > 0; i++, len--) {
    dest[i] = src[i];
  }
  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return dest;
}

// сравнивает первые n байтов str1 и str2.
// возвращает 0, если строки равны и разницу между первыми неравными символами,
// если нет
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  int flag = 1;
  for (s21_size_t i = 0; flag && i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      res = str1[i] - str2[i];
      flag = 0;
    }
  }
  return res;
}

// поиск первого вхождения c в строке str
char *s21_strchr(const char *str, int c) {
  const char *output = S21_NULL;
  s21_size_t len_str = s21_strlen(str);

  for (s21_size_t i = 0; i <= len_str; ++i) {
    if (str[i] == c) {
      output = str + i;
      break;
    }
  }
  return (char *)output;
}

// Добавляет строку src в конец строки dest длиной до n символов
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  const char *to_add = src;
  s21_size_t len_dest = s21_strlen(dest);

  for (s21_size_t i = 0; i <= len_dest; i++) {
    if (dest[i] == '\0') {
      for (s21_size_t k = 0; k < n; k++) {
        dest[i + k] = to_add[k];
      }
    }
  }
  dest[len_dest + n] = '\0';
  return dest;
}

// копирует c в первые n символов строки str
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *array = str;
  for (s21_size_t i = 0; i < n; ++i) {
    array[i] = c;
  }
  return str;
}

// Копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *array = dest;
  const unsigned char *to_put = src;

  for (s21_size_t i = 0; i < n; i++) {
    array[i] = to_put[i];
  }
  return array;
}

// Сравнивает первые n байтов str1 и str2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *array1 = str1;
  const unsigned char *array2 = str2;
  int res = 0;
  int flag = 1;
  for (s21_size_t i = 0; i < n && flag; i++) {
    if (array1[i] != array2[i]) {
      res = array1[i] - array2[i];
      flag = 0;
    }
  }
  return res;
}

// поиск первого вхождения c в первых n байтах str
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *array = str;
  const unsigned char *res = S21_NULL;

  for (s21_size_t i = 0; i < n; i++) {
    if (array[i] == c) {
      res = array + i;
    }
  }
  return (void *)res;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (*str++) {
    len++;
  }
  return len;
}

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char res[1000] = "";
  int isnull = 1;
  int j = 0, m = s21_strlen(delim), flag = 0, len_new_str = 0, len_delim = 0;
  if (delim != NULL) {
    static char *str1 = NULL;
    static int i2 = 0, i3 = 0, i = 0;
    if (str != NULL) {
      str1 = str;
      i = s21_strlen(str1);
      for (; j < i; j++) {
        for (int n = 0; n < m; n++) {
          if (str1[j] == delim[n]) {
            if (i2 != 0) {
              flag++;
            } else {
              i3++;
            }
            j++;
            n = 0;
          } else {
            if ((str1[j] != delim[n] && n == m - 1 && flag == 0)) {
              res[i2] = str1[j];
              i2++;
              isnull = 0;
            }
          }
        }
      }
    } else {
      for (int u = 0; u < 1000; u++) res[u] = '\0';
      s21_str_eq_null(delim, str, str1, res, j, &i2, &i3, &i, m, len_delim,
                      len_new_str, flag, &isnull);
    }
  }
  return isnull ? S21_NULL : res;
}
// Вспомогательная функция
void s21_str_eq_null(const char *delim, char *str, char *str1, char *res, int j,
                     int *i2, int *i3, int *i, int m, int len_delim,
                     int len_new_str, int flag, int *isnull) {
  if (str == S21_NULL) {
    j = *i2 + *i3;
    if (j < *i) {
      for (; j < *i; j++) {
        flag = 0;
        for (int n = 0; n < m; n++) {
          if (str1[j] == delim[n]) {
            if (len_new_str != 0) {
              flag++;
              j = *i;
            } else {
              len_delim++;
              (*i3)++;
            }
            j++;
            n = -1;
          } else {
            if ((n == m - 1 && str1[j] != delim[n] && flag == 0)) {
              res[len_new_str] = str1[j];
              (*i2)++;
              len_new_str++;
              *isnull = 0;
            }
          }
        }
      }
    }
  }
}
