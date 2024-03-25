#include "s21_string.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sprintf.h"

// memchr tests
START_TEST(s21_memchr_test_1) {
  s21_size_t len = 12;
  char str[] = "Hello world";
  char chr = 'w';
  ck_assert_pstr_eq(s21_memchr(str, chr, len), memchr(str, chr, len));
}
END_TEST

START_TEST(s21_memchr_test_2) {
  s21_size_t len = 3;
  char str[] = "Hello world";
  char chr = 'w';
  ck_assert_pstr_eq(s21_memchr(str, chr, len), memchr(str, chr, len));
}
END_TEST

START_TEST(s21_memchr_test_3) {
  s21_size_t len = 12;
  char str[] = "Hello world";
  char chr = 'z';
  ck_assert_pstr_eq(s21_memchr(str, chr, len), memchr(str, chr, len));
}
END_TEST

START_TEST(s21_memchr_test_4) {
  s21_size_t len = 12;
  char str[] = "ma\n\r";
  char chr = 'n';
  ck_assert_pstr_eq(s21_memchr(str, chr, len), memchr(str, chr, len));
}
END_TEST

START_TEST(s21_memchr_test_5) {
  s21_size_t len = 12;
  char str[] = " \0\0 n a \0";
  char chr = 'a';
  ck_assert_pstr_eq(s21_memchr(str, chr, len), memchr(str, chr, len));
}
END_TEST

// memcmp tests
START_TEST(s21_memcmp_test_1) {
  s21_size_t len = 6;
  char str1[] = "hello";
  char str2[] = "there";
  ck_assert_int_eq(s21_memcmp(str1, str2, len), memcmp(str1, str2, len));
}
END_TEST

START_TEST(s21_memcmp_test_2) {
  s21_size_t len = 6;
  char str1[] = "hello";
  char str2[] = "hello";
  ck_assert_int_eq(s21_memcmp(str1, str2, len), memcmp(str1, str2, len));
}
END_TEST

START_TEST(s21_memcmp_test_3) {
  s21_size_t len = 10;
  char str1[] = "\nhello";
  char str2[] = "\nhi there";
  ck_assert_int_eq(s21_memcmp(str1, str2, len), memcmp(str1, str2, len));
}
END_TEST

// memcpy tests
START_TEST(s21_memcpy_test_1) {
  s21_size_t len = 6;
  char dest[20] = "";
  char str[20] = "hello";
  ck_assert_pstr_eq(s21_memcpy(dest, str, len), memcpy(dest, str, len));
}
END_TEST

START_TEST(s21_memcpy_test_2) {
  s21_size_t len = 5;
  char dest[20] = "";
  char str[20] = "";
  ck_assert_pstr_eq(s21_memcpy(dest, str, len), memcpy(dest, str, len));
}
END_TEST

START_TEST(s21_memcpy_test_3) {
  s21_size_t len = 7;
  char dest[50] = "";
  char str[50] = "Hello there. How are you today?";
  ck_assert_pstr_eq(s21_memcpy(dest, str, len), memcpy(dest, str, len));
}
END_TEST

// memset tests
START_TEST(s21_memset_test_1) {
  s21_size_t len = 5;
  char dest[20] = "hello";
  int c = 'a';
  ck_assert_pstr_eq(s21_memset(dest, c, len), memset(dest, c, len));
}
END_TEST

START_TEST(s21_memset_test_2) {
  s21_size_t len = 5;
  char dest[20] = "";
  int c = 'a';
  ck_assert_pstr_eq(s21_memset(dest, c, len), memset(dest, c, len));
}
END_TEST

START_TEST(s21_memset_test_3) {
  s21_size_t len = 2;
  char dest[20] = "\n\n\n\0";
  int c = 'a';
  ck_assert_pstr_eq(s21_memset(dest, c, len), memset(dest, c, len));
}
END_TEST

START_TEST(s21_memset_test_4) {
  s21_size_t len = 2;
  char dest[20] = "aaa\na\n";
  int c = '\n';
  ck_assert_pstr_eq(s21_memset(dest, c, len), memset(dest, c, len));
}
END_TEST

// strncat test
START_TEST(s21_strncat_test_1) {
  s21_size_t len = 6;
  char dest[20] = "hello ";
  char src[20] = "there";
  ck_assert_pstr_eq(s21_strncat(dest, src, len), strncat(dest, src, len));
}
END_TEST

START_TEST(s21_strncat_test_2) {
  s21_size_t len = 6;
  char dest[20] = "";
  char src[20] = "there";
  ck_assert_pstr_eq(s21_strncat(dest, src, len), strncat(dest, src, len));
}
END_TEST

START_TEST(s21_strncat_test_3) {
  s21_size_t len = 6;
  char dest[20] = "\0";
  char src[20] = "\0\0\0\0";
  ck_assert_pstr_eq(s21_strncat(dest, src, len), strncat(dest, src, len));
}
END_TEST

// strchr tests
START_TEST(s21_strchr_test_1) {
  char arr[20] = "hello";
  char c = 'h';
  ck_assert_pstr_eq(s21_strchr(arr, c), strchr(arr, c));
}
END_TEST

START_TEST(s21_strchr_test_2) {
  char arr[20] = "hello";
  char c = '\0';
  ck_assert_pstr_eq(s21_strchr(arr, c), strchr(arr, c));
}
END_TEST

START_TEST(s21_strchr_test_3) {
  char arr[20] = "hello";
  char c = 'm';
  ck_assert_pstr_eq(s21_strchr(arr, c), strchr(arr, c));
}
END_TEST

START_TEST(s21_strchr_test_4) {
  char arr[20] = "\0\0\n";
  char c = '\n';
  ck_assert_pstr_eq(s21_strchr(arr, c), strchr(arr, c));
}
END_TEST

// strncmp tests
START_TEST(s21_strncmp_test_1) {
  s21_size_t len = 10;
  const char str1[] = "it's october";
  const char str2[] = "it's october";
  ck_assert_int_eq(s21_strncmp(str1, str2, len), strncmp(str1, str2, len));
}
END_TEST

START_TEST(s21_strncmp_test_2) {
  s21_size_t len = 10;
  const char str1[] = "hel\0lo";
  const char str2[] = "hel\0lo";
  ck_assert_int_eq(s21_strncmp(str1, str2, len), strncmp(str1, str2, len));
}
END_TEST

START_TEST(s21_strncmp_test_3) {
  s21_size_t len = 10;
  const char str1[] = "hel\0lo";
  const char str2[] = "hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, len), strncmp(str1, str2, len));
}
END_TEST

START_TEST(s21_strncmp_test_4) {
  s21_size_t len = 2;
  const char str1[] = "";
  const char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, len), strncmp(str1, str2, len));
}
END_TEST

START_TEST(s21_strncmp_test_5) {
  s21_size_t len = 3;
  const char str1[] = "hola";
  const char str2[] = "holaaaaaaa";
  ck_assert_int_eq(s21_strncmp(str1, str2, len), strncmp(str1, str2, len));
}
END_TEST

// strncpy tests
START_TEST(s21_strncpy_test_1) {
  s21_size_t len = 2;
  char str1[40] = "";
  const char str2[20] = "hi there";
  ck_assert_pstr_eq(s21_strncpy(str1, str2, len), strncpy(str1, str2, len));
}
END_TEST

START_TEST(s21_strncpy_test_2) {
  s21_size_t len = 10;
  char str1[40] = "aaaaa";
  const char str2[20] = "hi";
  ck_assert_pstr_eq(s21_strncpy(str1, str2, len), strncpy(str1, str2, len));
}
END_TEST

START_TEST(s21_strncpy_test_3) {
  s21_size_t len = 5;
  char str1[40] = "aaaa";
  const char str2[20] = "\n\n\nhi";
  ck_assert_pstr_eq(s21_strncpy(str1, str2, len), strncpy(str1, str2, len));
}
END_TEST

// strcspn tests
START_TEST(s21_strcspn_test_1) {
  const char str1[] = "hello";
  const char str2[] = "abcdefjh";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test_2) {
  const char str1[] = "hello";
  const char str2[] = "\0";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test_3) {
  const char str1[] = "hello";
  const char str2[] = "abc";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test_4) {
  const char str1[] = "hello";
  const char str2[] = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// strpbrk tests
START_TEST(s21_strpbrk_test_1) {
  const char str1[] = "hello";
  const char str2[] = "lllllll";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_2) {
  const char str1[] = "hello";
  const char str2[] = "hgfdsa";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_3) {
  const char str1[] = "hel\n\0lo";
  const char str2[] = "hjko";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_4) {
  const char str1[] = "hel\n\0lo";
  const char str2[] = "he";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// strlen tests
START_TEST(s21_strlen_test_1) {
  const char str[] = "";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(s21_strlen_test_2) {
  const char str[] = "It's october!";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(s21_strlen_test_3) {
  const char str[] = "\0\n\0   ";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

// strstr tests
START_TEST(s21_strstr_test_1) {
  const char str1[] = "hello";
  const char str2[] = "he";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(s21_strstr_test_2) {
  const char str1[] = "hello";
  const char str2[] = "nopeeee";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(s21_strstr_test_3) {
  const char str1[] = "hello";
  const char str2[] = "";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(s21_strstr_test_4) {
  const char str1[] = "hello";
  const char str2[] = "lo";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(s21_strstr_test_5) {
  const char str1[] = "hello\0hi";
  const char str2[] = "hi";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

// strerror tests
START_TEST(s21_strerror_test_1) {
  ck_assert_pstr_eq(s21_strerror(2), strerror(2));
}
END_TEST

START_TEST(s21_strerror_test_2) {
  ck_assert_pstr_eq(s21_strerror(20), strerror(20));
}
END_TEST

START_TEST(s21_strerror_test_3) {
  char *res = s21_strerror(500);
  char *res_ok = strerror(500);
  ck_assert_pstr_eq(res, res_ok);
}
END_TEST

START_TEST(s21_strerror_test_4) {
  ck_assert_pstr_eq(s21_strerror(-34), strerror(-34));
}
END_TEST

// strrchr tests
START_TEST(s21_strrchr_test_1) {
  const char str1[] = "hello";
  int c = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST

START_TEST(s21_strrchr_test_2) {
  const char str1[] = "hel\0\0lo";
  int c = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST

START_TEST(s21_strrchr_test_3) {
  const char str1[] = "hello";
  int c = 'm';
  ck_assert_pstr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST

START_TEST(s21_strrchr_test_4) {
  const char str1[] = "";
  int c = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST

// to_upper tests
START_TEST(s21_to_upper_test_1) {
  char arr[20] = "hello";
  char *res = s21_to_upper(arr);
  char res_ok[20] = "HELLO";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char arr[30] = "hello\n\n1234hola";
  char *res = s21_to_upper(arr);
  char res_ok[30] = "HELLO\n\n1234HOLA";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_to_upper_test_3) {
  char arr[30] = "HELLO\0h";
  char *res = s21_to_upper(arr);
  char res_ok[30] = "HELLO";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

// to_lower tests
START_TEST(s21_to_lower_test_1) {
  char arr[20] = "HELLO";
  char *res = s21_to_lower(arr);
  char res_ok[20] = "hello";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  char arr[20] = "HE\n\n12345LLO";
  char *res = s21_to_lower(arr);
  char res_ok[20] = "he\n\n12345llo";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_to_lower_test_3) {
  char arr[20] = "hello";
  char *res = s21_to_lower(arr);
  char res_ok[20] = "hello";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

// trim tests
START_TEST(s21_trim_test_1) {
  char arr[20] = "abcabc123abc";
  char str[10] = "abc";
  char *res = s21_trim(arr, str);
  char res_ok[20] = "123";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_trim_test_2) {
  char arr[30] = "nnnnnnnnnnnnn";
  char str[10] = "n";
  char *res = s21_trim(arr, str);
  char res_ok[20] = "";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_trim_test_3) {
  char arr[30] = "nmnmnmnmnmnmnnnnmmm";
  char str[10] = "nm";
  char *res = s21_trim(arr, str);
  char res_ok[20] = "";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_trim_test_4) {
  char arr[30] = "hello";
  char str[10] = "mn";
  char *res = s21_trim(arr, str);
  char res_ok[20] = "hello";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_trim_test_5) {
  char arr[30] = "nnnmhello";
  char str[10] = "mn";
  char *res = s21_trim(arr, str);
  char res_ok[20] = "hello";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_trim_test_6) {
  char arr[30] = "hellonnmnmn";
  char str[10] = "mn";
  char *res = s21_trim(arr, str);
  char res_ok[20] = "hello";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

// insert tests
START_TEST(s21_insert_test_1) {
  char *arr = malloc(10 * sizeof(char));
  arr[0] = 'a';
  arr[1] = '\0';
  char *str = NULL;
  char *res = s21_insert(arr, str, 1);

  ck_assert_ptr_null(res);
  free(res);
  free(arr);
}
END_TEST

START_TEST(s21_insert_test_2) {
  char arr[30] = "efg";
  char str[10] = "abcd";
  char *res = s21_insert(arr, str, 0);
  char res_ok[20] = "abcdefg";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_insert_test_3) {
  char arr[30] = "abcdefg";
  char str[10] = "ab";
  char *res = s21_insert(arr, str, 20);
  char res_ok[20] = "abcdefg";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_insert_test_4) {
  char arr[30] = "abcdefg";
  char str[10] = "12";
  char *res = s21_insert(arr, str, 2);
  char res_ok[20] = "ab12cdefg";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

START_TEST(s21_insert_test_5) {
  char arr[30] = "";
  char str[10] = "abcd";
  char *res = s21_insert(arr, str, 0);
  char res_ok[20] = "abcd";

  ck_assert_pstr_eq(res, res_ok);
  free(res);
}
END_TEST

// strtok tests
START_TEST(s21_strtok_test_1) {
  char arr[50] = "hello0schowwwwewqeqweqweqweqeol3wdd7w";
  char str[10] = "qow";
  char *res = s21_strtok(arr, str);
  char *res2 = strtok(arr, str);
  res2 = strtok(NULL, str);
  res2 = strtok(NULL, str);
  res = s21_strtok(NULL, str);
  res = s21_strtok(NULL, str);
  ck_assert_pstr_eq(res, res2);
}
END_TEST

START_TEST(s21_strtok_test_2) {
  char arr[50] = "hello0 scho98ol457896!!!";
  char str[10] = "09876543";
  char *res = s21_strtok(arr, str);
  res = s21_strtok(NULL, str);
  char *res2 = strtok(arr, str);
  res2 = strtok(NULL, str);
  ck_assert_pstr_eq(res, res2);
}
END_TEST

START_TEST(s21_strtok_test_3) {
  char arr[50] = "./privet-./hello";
  char str[10] = "./";
  char *res = s21_strtok(arr, str);
  char *res2 = strtok(arr, str);
  ck_assert_pstr_eq(res, res2);
}
END_TEST

START_TEST(s21_strtok_test_4) {
  char arr[50] = "\0\0\0\0\efefef";
  char str[10] = "\0e";
  char *res = s21_strtok(arr, str);
  char *res2 = strtok(arr, str);
  res2 = strtok(NULL, str);
  res2 = strtok(NULL, str);
  res = s21_strtok(NULL, str);
  res = s21_strtok(NULL, str);
  res2 = strtok(NULL, str);
  res = s21_strtok(NULL, str);
  res2 = strtok(NULL, str);
  res = s21_strtok(NULL, str);
  ck_assert_pstr_eq(res, res2);
}
END_TEST

START_TEST(s21_strtok_test_5) {
  char arr[50] = "hi   miach emicala ll    bl  ue";
  char str[10] = "ia";
  char *res = s21_strtok(arr, str);
  res = s21_strtok(NULL, str);
  res = s21_strtok(NULL, str);
  res = s21_strtok(NULL, str);
  char *res2 = strtok(arr, str);
  res2 = strtok(NULL, str);
  res2 = strtok(NULL, str);
  res2 = strtok(NULL, str);
  ck_assert_pstr_eq(res, res2);
}
END_TEST
// Спецификатор f
START_TEST(s21_sprintf_f_test_1) {
  char arr[50], arr2[50];
  double k = 10.891;
  s21_sprintf(arr, "%.1f", k);
  sprintf(arr2, "%.1f", k);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_2) {
  char arr[50], arr2[50];
  double k = 19.99999, k2 = 9.99999;
  s21_sprintf(arr, "%.2f %.1f!", k, k2);
  sprintf(arr2, "%.2f %.1f!", k, k2);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_3) {
  char arr[50], arr2[50];
  double k = pow(10, 500);
  s21_sprintf(arr, "inf = %.5f", k);
  sprintf(arr2, "inf = %.5f", k);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_4) {
  char arr[50], arr2[50];
  double k = -10.891;
  s21_sprintf(arr, "-%.1f %.7f", k, k);
  sprintf(arr2, "-%.1f %.7f", k, k);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_5) {
  char arr[50], arr2[50];
  double n = -1 * pow(10, 1000);
  s21_sprintf(arr, "abc%05fm", n);
  sprintf(arr2, "abc%05fm", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_6) {
  char arr[50], arr2[50];
  double n = pow(10, 1000);
  s21_sprintf(arr, "abc% 5fm", n);
  sprintf(arr2, "abc% 5fm", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_7) {
  char arr[50], arr2[50];
  double n = pow(10, 10);
  s21_sprintf(arr, "abc%05fm", n);
  sprintf(arr2, "abc%05fm", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_8) {
  char arr[50], arr2[50];
  double n = -1 * pow(10, 10);
  s21_sprintf(arr, "abc+%#05fm", -n);
  sprintf(arr2, "abc+%#05fm", -n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_9) {
  char arr[50], arr2[50];
  double n = -100;
  s21_sprintf(arr, "-%-5fm", -n);
  sprintf(arr2, "-%-5fm", -n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_10) {
  char arr[50], arr2[50];
  long double n = -100;
  s21_sprintf(arr, "ddd-%-5Lfm", -n);
  sprintf(arr2, "ddd-%-5Lfm", -n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_f_test_11) {
  char arr[50], arr2[50];
  long double n = pow(10, 10000);
  s21_sprintf(arr, "%05Lfb", n);
  sprintf(arr2, "%05Lfb", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST
// Спецификатор c
START_TEST(s21_sprintf_c_test_1) {
  char arr[50], arr2[50];
  int n = -10;
  s21_sprintf(arr, "-%-c=%c", -n, n);
  sprintf(arr2, "-%-c=%c", -n, n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_c_test_2) {
  char arr[50], arr2[50];
  int n = pow(10, 1000);
  s21_sprintf(arr, "aaaaa+%10c", -n);
  sprintf(arr2, "aaaaa+%10c", -n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_c_test_3) {
  char arr[50], arr2[50];
  int n = 34.9999;
  s21_sprintf(arr, "%c", -n);
  sprintf(arr2, "%c", -n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

// Спецификатор d
START_TEST(s21_sprintf_d_test_1) {
  char str1[40], str2[40];
  const char format[40] = "abc%dabc";
  int n = 6;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_2) {
  char str1[40], str2[40];
  const char format[40] = "abc%.3d";
  int n = -5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_3) {
  char str1[40], str2[40];
  const char format[40] = "abc%-20.3da";
  int n = -5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_4) {
  char str1[40], str2[40];
  const char format[40] = "abc%+5.2d";
  int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_5) {
  char str1[40], str2[40];
  const char format[40] = "abc%+-5.2d";
  int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_6) {
  char str1[40], str2[40];
  const char format[40] = "abc%05d";
  int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_7) {
  char str1[40], str2[40];
  const char format[40] = "abc%+5d";
  int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_8) {
  char str1[40], str2[40];
  const char format[40] = "abc%+05d";
  int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_9) {
  char str1[40], str2[40];
  const char format[40] = "abc%.0d";
  int n = 0;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_10) {
  char str1[40], str2[40];
  const char format[40] = "abc% 10.4d";
  int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_11) {
  char str1[40], str2[40];
  const char format[40] = "abc%5.2hd";
  unsigned short int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_12) {
  char str1[40], str2[40];
  const char format[40] = "abc%5.2ld";
  unsigned long int n = 5;
  s21_sprintf(str1, format, n);
  sprintf(str2, format, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST
// Спецификатор s
START_TEST(s21_sprintf_s_test_1) {
  char arr[50], arr2[50];
  char n[10] = "go next";
  s21_sprintf(arr, "%s", n);
  sprintf(arr2, "%s", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_s_test_2) {
  char arr[50], arr2[50];
  char n[10] = "qweqwe";
  s21_sprintf(arr, "%-5s %-4.0s", n, n);
  sprintf(arr2, "%-5s %-4.0s", n, n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_s_test_3) {
  char arr[50], arr2[50];
  char n[10] = "////0000";
  s21_sprintf(arr, "%.0s %-4.0s", n, n);
  sprintf(arr2, "%.0s %-4.0s", n, n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST
// Спецификатор g/G
START_TEST(s21_sprintf_g_test_1) {
  char arr[50], arr2[50];
  double n = 924.9119;
  s21_sprintf(arr, "%1.3g", n);
  sprintf(arr2, "%1.3g", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_g_test_2) {
  char arr[50], arr2[50];
  double n = 10000234.9119;
  s21_sprintf(arr, "%2.0g", n);
  sprintf(arr2, "%2.0g", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_g_test_3) {
  char arr[50], arr2[50];
  long double n = 100123400234.9119;
  s21_sprintf(arr, "%-8Lg", n);
  sprintf(arr2, "%-8Lg", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_g_test_4) {
  char arr[50], arr2[50];
  long double n = pow(10, 5000);
  s21_sprintf(arr, "%-8Lg", n);
  sprintf(arr2, "%-8Lg", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_g_test_5) {
  char arr[50], arr2[50];
  double n = pow(10, 50);
  s21_sprintf(arr, "%-8G %%123", n);
  sprintf(arr2, "%-8G %%123", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST
// Спецификатор e
START_TEST(s21_sprintf_e_test_1) {
  char arr[50], arr2[50];
  double n = -9.999;
  s21_sprintf(arr, "% *.*e 12", 1, 0, n);
  sprintf(arr2, "% *.*e 12", 1, 0, n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_2) {
  char arr[50], arr2[50];
  double n = 123.45;
  s21_sprintf(arr, "%+.12E 12", n);
  sprintf(arr2, "%+.12E 12", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_3) {
  char arr[50], arr2[50];
  double n = 0.00012346;
  s21_sprintf(arr, "% .3e 12", n);
  sprintf(arr2, "% .3e 12", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_4) {
  char arr[50], arr2[50];
  double n = 12346;
  s21_sprintf(arr, "%012.3e 12.3", n);
  sprintf(arr2, "%012.3e 12.3", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_5) {
  char arr[50], arr2[50];
  long double n = 0;
  s21_sprintf(arr, "123 %Le 12.3", n);
  sprintf(arr2, "123 %Le 12.3", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_6) {
  char arr[50], arr2[50];
  long double n = 1234567;
  s21_sprintf(arr, "123 %LE 12.3", n);
  sprintf(arr2, "123 %LE 12.3", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_7) {
  char arr[50], arr2[50];
  long double n = 13498;
  s21_sprintf(arr, "123 %0+.3LE 12.3", n);
  sprintf(arr2, "123 %0+.3LE 12.3", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_e_test_8) {
  char arr[50], arr2[50];
  long double n = 123;
  s21_sprintf(arr, "123 %- Le 12.3", n);
  sprintf(arr2, "123 %- Le 12.3", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_1) {
  char arr[50], arr2[50];
  unsigned int n = 1024925;
  s21_sprintf(arr, "%-8.5o", n);
  sprintf(arr2, "%-8.5o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_2) {
  char arr[50], arr2[50];
  unsigned int n = 8882345;
  s21_sprintf(arr, "%#-.3o", n);
  sprintf(arr2, "%#-.3o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_3) {
  char arr[50], arr2[50];
  unsigned int n = 8882345;
  s21_sprintf(arr, "%#-.3o", n);
  sprintf(arr2, "%#-.3o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_4) {
  char arr[50], arr2[50];
  unsigned int n = pow(10, 100000);
  s21_sprintf(arr, "-%0o", -n);
  sprintf(arr2, "-%0o", -n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_5) {
  char arr[50], arr2[50];
  unsigned int n = 0;
  s21_sprintf(arr, "%#.o", n);
  sprintf(arr2, "%#.o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_6) {
  char arr[50], arr2[50];
  unsigned int n = 0;
  s21_sprintf(arr, "%-#.o", n);
  sprintf(arr2, "%-#.o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_7) {
  char arr[50], arr2[50];
  unsigned int n = 16;
  s21_sprintf(arr, "%-7o", n);
  sprintf(arr2, "%-7o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_o_test_8) {
  char arr[50], arr2[50];
  unsigned int n = 16;
  s21_sprintf(arr, "%#7o", n);
  sprintf(arr2, "%#7o", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_u_test_1) {
  char arr[50], arr2[50];
  unsigned int n = 0;
  s21_sprintf(arr, "%-7u", n);
  sprintf(arr2, "%-7u", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_u_test_2) {
  char arr[50], arr2[50];
  unsigned int n = 16;
  s21_sprintf(arr, "%hu", n);
  sprintf(arr2, "%hu", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_u_test_3) {
  char arr[50], arr2[50];
  unsigned int n = pow(10, 4000);
  s21_sprintf(arr, "%0u", n);
  sprintf(arr2, "%0u", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_1) {
  char arr[50], arr2[50];
  unsigned int n = pow(10, 4000);
  s21_sprintf(arr, "aadd%0x", n);
  sprintf(arr2, "aadd%0x", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_2) {
  char arr[50], arr2[50];
  unsigned int n = 0;
  s21_sprintf(arr, "%0x", n);
  sprintf(arr2, "%0x", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_3) {
  char arr[50], arr2[50];
  unsigned int n = 0;
  s21_sprintf(arr, "%-.6hx", n);
  sprintf(arr2, "%-.6hx", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_4) {
  char arr[50], arr2[50];
  unsigned int n = 155;
  s21_sprintf(arr, "%#-.6x pfewkwe %#-.6x ==", n, n);
  sprintf(arr2, "%#-.6x pfewkwe %#-.6x ==", n, n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_5) {
  char arr[50], arr2[50];
  unsigned int n = 189324000;
  s21_sprintf(arr, "%#8.5x", n);
  sprintf(arr2, "%#8.5x", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_6) {
  char arr[50], arr2[50];
  unsigned int n = 1346346341;
  s21_sprintf(arr, "wwfkljw%9.5x", n);
  sprintf(arr2, "wwfkljw%9.5x", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_7) {
  char arr[50], arr2[50];
  unsigned int n = 189000;
  s21_sprintf(arr, "%5.5xh", n);
  sprintf(arr2, "%5.5xh", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_x_test_8) {
  char arr[50], arr2[50];
  unsigned int n = 189000;
  s21_sprintf(arr, "%8.5Xh", n);
  sprintf(arr2, "%8.5Xh", n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_n_test_1) {
  char arr[50], arr2[50];
  unsigned int n = 1346346341;
  s21_sprintf(arr, "rr%n", &n);
  sprintf(arr2, "rr%n", &n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_n_test_2) {
  char arr[50], arr2[50];
  unsigned int n = 134;
  s21_sprintf(arr, "%n.3rr%n", &n, &n);
  sprintf(arr2, "%n.3rr%n", &n, &n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_n_test_3) {
  char arr[50], arr2[50];
  unsigned int n = 734645551;
  s21_sprintf(arr, "wqeweqwqe%n", &n);
  sprintf(arr2, "wqeweqwqe%n", &n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_p_test_1) {
  char arr[50], arr2[50];
  unsigned int n = 734645551;
  s21_sprintf(arr, "qweqwe%p 324234", &n);
  sprintf(arr2, "qweqwe%p 324234", &n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_p_test_2) {
  char arr[50], arr2[50];
  unsigned int n = 7;
  s21_sprintf(arr, "%p", &n);
  sprintf(arr2, "%p", &n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_p_test_3) {
  char arr[50], arr2[50];
  unsigned int n = 12;
  s21_sprintf(arr, "%-20p", &n);
  sprintf(arr2, "%-20p", &n);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST
// Комбинации спецификаторов
START_TEST(s21_sprintf_combo_test_1) {
  char arr[100], arr2[100];
  unsigned int n = 12;
  double d = 123.45;
  s21_sprintf(arr, "%-20p %%sdedf%13.5o % f %+E 1", &n, n, d, d);
  sprintf(arr2, "%-20p %%sdedf%13.5o % f %+E 1", &n, n, d, d);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

START_TEST(s21_sprintf_combo_test_2) {
  char arr[100], arr2[100];
  char s[] = "biba && boba";
  unsigned long int n = 6213;
  unsigned short u = (unsigned short)23455;
  long double d = 123.45;
  s21_sprintf(arr, "%hu %%dedf%-15.2lo %.5s f %+.3Lg 1", u, n, s, d);
  sprintf(arr2, "%hu %%dedf%-15.2lo %.5s f %+.3Lg 1", u, n, s, d);
  ck_assert_pstr_eq(arr, arr2);
}
END_TEST

Suite *s21_sprintf_combo_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_combo_core");
  Suite *s = suite_create("s21_sprintf_combo_tests");

  tcase_add_test(tc, s21_sprintf_combo_test_1);
  tcase_add_test(tc, s21_sprintf_combo_test_2);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_p_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_p_core");
  Suite *s = suite_create("s21_sprintf_p_tests");

  tcase_add_test(tc, s21_sprintf_p_test_1);
  tcase_add_test(tc, s21_sprintf_p_test_2);
  tcase_add_test(tc, s21_sprintf_p_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_n_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_n_core");
  Suite *s = suite_create("s21_sprintf_n_tests");

  tcase_add_test(tc, s21_sprintf_n_test_1);
  tcase_add_test(tc, s21_sprintf_n_test_2);
  tcase_add_test(tc, s21_sprintf_n_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_x_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_x_core");
  Suite *s = suite_create("s21_sprintf_x_tests");

  tcase_add_test(tc, s21_sprintf_x_test_1);
  tcase_add_test(tc, s21_sprintf_x_test_2);
  tcase_add_test(tc, s21_sprintf_x_test_3);
  tcase_add_test(tc, s21_sprintf_x_test_4);
  tcase_add_test(tc, s21_sprintf_x_test_5);
  tcase_add_test(tc, s21_sprintf_x_test_6);
  tcase_add_test(tc, s21_sprintf_x_test_7);
  tcase_add_test(tc, s21_sprintf_x_test_8);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_u_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_u_core");
  Suite *s = suite_create("s21_sprintf_u_tests");

  tcase_add_test(tc, s21_sprintf_u_test_1);
  tcase_add_test(tc, s21_sprintf_u_test_2);
  tcase_add_test(tc, s21_sprintf_u_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_o_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_o_core");
  Suite *s = suite_create("s21_sprintf_o_tests");

  tcase_add_test(tc, s21_sprintf_o_test_1);
  tcase_add_test(tc, s21_sprintf_o_test_2);
  tcase_add_test(tc, s21_sprintf_o_test_3);
  tcase_add_test(tc, s21_sprintf_o_test_4);
  tcase_add_test(tc, s21_sprintf_o_test_5);
  tcase_add_test(tc, s21_sprintf_o_test_6);
  tcase_add_test(tc, s21_sprintf_o_test_7);
  tcase_add_test(tc, s21_sprintf_o_test_8);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_e_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_e_core");
  Suite *s = suite_create("s21_sprintf_e_tests");

  tcase_add_test(tc, s21_sprintf_e_test_1);
  tcase_add_test(tc, s21_sprintf_e_test_2);
  tcase_add_test(tc, s21_sprintf_e_test_3);
  tcase_add_test(tc, s21_sprintf_e_test_4);
  tcase_add_test(tc, s21_sprintf_e_test_5);
  tcase_add_test(tc, s21_sprintf_e_test_6);
  tcase_add_test(tc, s21_sprintf_e_test_7);
  tcase_add_test(tc, s21_sprintf_e_test_8);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_g_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_g_core");
  Suite *s = suite_create("s21_sprintf_g_tests");

  tcase_add_test(tc, s21_sprintf_g_test_1);
  tcase_add_test(tc, s21_sprintf_g_test_2);
  tcase_add_test(tc, s21_sprintf_g_test_3);
  tcase_add_test(tc, s21_sprintf_g_test_4);
  tcase_add_test(tc, s21_sprintf_g_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_d_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_d_core");
  Suite *s = suite_create("s21_sprintf_d_tests");

  tcase_add_test(tc, s21_sprintf_d_test_1);
  tcase_add_test(tc, s21_sprintf_d_test_2);
  tcase_add_test(tc, s21_sprintf_d_test_3);
  tcase_add_test(tc, s21_sprintf_d_test_4);
  tcase_add_test(tc, s21_sprintf_d_test_5);
  tcase_add_test(tc, s21_sprintf_d_test_6);
  tcase_add_test(tc, s21_sprintf_d_test_7);
  tcase_add_test(tc, s21_sprintf_d_test_8);
  tcase_add_test(tc, s21_sprintf_d_test_9);
  tcase_add_test(tc, s21_sprintf_d_test_10);
  tcase_add_test(tc, s21_sprintf_d_test_11);
  tcase_add_test(tc, s21_sprintf_d_test_12);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_s_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_s_core");
  Suite *s = suite_create("s21_sprintf_s_tests");

  tcase_add_test(tc, s21_sprintf_s_test_1);
  tcase_add_test(tc, s21_sprintf_s_test_2);
  tcase_add_test(tc, s21_sprintf_s_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_c_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_c_core");
  Suite *s = suite_create("s21_sprintf_c_tests");

  tcase_add_test(tc, s21_sprintf_c_test_1);
  tcase_add_test(tc, s21_sprintf_c_test_2);
  tcase_add_test(tc, s21_sprintf_c_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sprintf_f_suite(void) {
  TCase *tc = tcase_create("s21_sprintf_f_core");
  Suite *s = suite_create("s21_sprintf_f_tests");

  tcase_add_test(tc, s21_sprintf_f_test_1);
  tcase_add_test(tc, s21_sprintf_f_test_2);
  tcase_add_test(tc, s21_sprintf_f_test_3);
  tcase_add_test(tc, s21_sprintf_f_test_4);
  tcase_add_test(tc, s21_sprintf_f_test_5);
  tcase_add_test(tc, s21_sprintf_f_test_6);
  tcase_add_test(tc, s21_sprintf_f_test_7);
  tcase_add_test(tc, s21_sprintf_f_test_8);
  tcase_add_test(tc, s21_sprintf_f_test_9);
  tcase_add_test(tc, s21_sprintf_f_test_10);
  tcase_add_test(tc, s21_sprintf_f_test_11);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_insert_suite(void) {
  TCase *tc = tcase_create("s21_insert_core");
  Suite *s = suite_create("s21_insert_tests");

  tcase_add_test(tc, s21_insert_test_1);
  tcase_add_test(tc, s21_insert_test_2);
  tcase_add_test(tc, s21_insert_test_3);
  tcase_add_test(tc, s21_insert_test_4);
  tcase_add_test(tc, s21_insert_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_trim_suite(void) {
  TCase *tc = tcase_create("s21_trim_core");
  Suite *s = suite_create("s21_trim_tests");

  tcase_add_test(tc, s21_trim_test_1);
  tcase_add_test(tc, s21_trim_test_2);
  tcase_add_test(tc, s21_trim_test_3);
  tcase_add_test(tc, s21_trim_test_4);
  tcase_add_test(tc, s21_trim_test_5);
  tcase_add_test(tc, s21_trim_test_6);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_to_lower_suite(void) {
  TCase *tc = tcase_create("s21_to_lower_core");
  Suite *s = suite_create("s21_to_lower_tests");

  tcase_add_test(tc, s21_to_lower_test_1);
  tcase_add_test(tc, s21_to_lower_test_2);
  tcase_add_test(tc, s21_to_lower_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_to_upper_suite(void) {
  TCase *tc = tcase_create("s21_to_upper_core");
  Suite *s = suite_create("s21_to_upper_tests");

  tcase_add_test(tc, s21_to_upper_test_1);
  tcase_add_test(tc, s21_to_upper_test_2);
  tcase_add_test(tc, s21_to_upper_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strrchr_suite(void) {
  TCase *tc = tcase_create("s21_strrchr_core");
  Suite *s = suite_create("s21_strrchr_tests");

  tcase_add_test(tc, s21_strrchr_test_1);
  tcase_add_test(tc, s21_strrchr_test_2);
  tcase_add_test(tc, s21_strrchr_test_3);
  tcase_add_test(tc, s21_strrchr_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strerror_suite(void) {
  TCase *tc = tcase_create("s21_strerror_core");
  Suite *s = suite_create("s21_strerror_tests");

  tcase_add_test(tc, s21_strerror_test_1);
  tcase_add_test(tc, s21_strerror_test_2);
  tcase_add_test(tc, s21_strerror_test_3);
  tcase_add_test(tc, s21_strerror_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strstr_suite(void) {
  TCase *tc = tcase_create("s21_strstr_core");
  Suite *s = suite_create("s21_strstr_tests");

  tcase_add_test(tc, s21_strstr_test_1);
  tcase_add_test(tc, s21_strstr_test_2);
  tcase_add_test(tc, s21_strstr_test_3);
  tcase_add_test(tc, s21_strstr_test_4);
  tcase_add_test(tc, s21_strstr_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strpbrk_suite(void) {
  TCase *tc = tcase_create("s21_strpbrk_core");
  Suite *s = suite_create("s21_strpbrk_tests");

  tcase_add_test(tc, s21_strpbrk_test_1);
  tcase_add_test(tc, s21_strpbrk_test_2);
  tcase_add_test(tc, s21_strpbrk_test_3);
  tcase_add_test(tc, s21_strpbrk_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strcspn_suite(void) {
  TCase *tc = tcase_create("s21_strcspn_core");
  Suite *s = suite_create("s21_strcspn_tests");

  tcase_add_test(tc, s21_strcspn_test_1);
  tcase_add_test(tc, s21_strcspn_test_2);
  tcase_add_test(tc, s21_strcspn_test_3);
  tcase_add_test(tc, s21_strcspn_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strncpy_suite(void) {
  TCase *tc = tcase_create("s21_strncpy_core");
  Suite *s = suite_create("s21_strncpy_tests");

  tcase_add_test(tc, s21_strncpy_test_1);
  tcase_add_test(tc, s21_strncpy_test_2);
  tcase_add_test(tc, s21_strncpy_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strncmp_suite(void) {
  TCase *tc = tcase_create("s21_strncmp_core");
  Suite *s = suite_create("s21_strncmp_tests");

  tcase_add_test(tc, s21_strncmp_test_1);
  tcase_add_test(tc, s21_strncmp_test_2);
  tcase_add_test(tc, s21_strncmp_test_3);
  tcase_add_test(tc, s21_strncmp_test_4);
  tcase_add_test(tc, s21_strncmp_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strchr_suite(void) {
  TCase *tc = tcase_create("s21_strchr_core");
  Suite *s = suite_create("s21_strchr_tests");

  tcase_add_test(tc, s21_strchr_test_1);
  tcase_add_test(tc, s21_strchr_test_2);
  tcase_add_test(tc, s21_strchr_test_3);
  tcase_add_test(tc, s21_strchr_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strncat_suite(void) {
  TCase *tc = tcase_create("s21_strncat_core");
  Suite *s = suite_create("s21_strncat_tests");

  tcase_add_test(tc, s21_strncat_test_1);
  tcase_add_test(tc, s21_strncat_test_2);
  tcase_add_test(tc, s21_strncat_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memset_suite(void) {
  TCase *tc = tcase_create("s21_memset_core");
  Suite *s = suite_create("s21_memset_tests");

  tcase_add_test(tc, s21_memset_test_1);
  tcase_add_test(tc, s21_memset_test_2);
  tcase_add_test(tc, s21_memset_test_3);
  tcase_add_test(tc, s21_memset_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memcpy_suite(void) {
  TCase *tc = tcase_create("s21_memcpy_core");
  Suite *s = suite_create("s21_memcpy_tests");

  tcase_add_test(tc, s21_memcpy_test_1);
  tcase_add_test(tc, s21_memcpy_test_2);
  tcase_add_test(tc, s21_memcpy_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memchr_suite(void) {
  TCase *tc = tcase_create("s21_memchr_core");
  Suite *s = suite_create("s21_memchr_tests");

  tcase_add_test(tc, s21_memchr_test_1);
  tcase_add_test(tc, s21_memchr_test_2);
  tcase_add_test(tc, s21_memchr_test_3);
  tcase_add_test(tc, s21_memchr_test_4);
  tcase_add_test(tc, s21_memchr_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memcmp_suite(void) {
  TCase *tc = tcase_create("s21_memcmp_core");
  Suite *s = suite_create("s21_memcmp_tests");

  tcase_add_test(tc, s21_memcmp_test_1);
  tcase_add_test(tc, s21_memcmp_test_2);
  tcase_add_test(tc, s21_memcmp_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strlen_suite(void) {
  TCase *tc = tcase_create("s21_strlen_core");
  Suite *s = suite_create("s21_strlen_tests");

  tcase_add_test(tc, s21_strlen_test_1);
  tcase_add_test(tc, s21_strlen_test_2);
  tcase_add_test(tc, s21_strlen_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strtok_suite(void) {
  TCase *tc = tcase_create("s21_strtok_core");
  Suite *s = suite_create("s21_strtok_tests");

  tcase_add_test(tc, s21_strtok_test_1);
  tcase_add_test(tc, s21_strtok_test_2);
  tcase_add_test(tc, s21_strtok_test_3);
  tcase_add_test(tc, s21_strtok_test_4);
  tcase_add_test(tc, s21_strtok_test_5);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr = S21_NULL;

  sr = srunner_create(s21_memchr_suite());
  srunner_add_suite(sr, s21_memcmp_suite());
  srunner_add_suite(sr, s21_memcpy_suite());
  srunner_add_suite(sr, s21_memset_suite());
  srunner_add_suite(sr, s21_strncat_suite());
  srunner_add_suite(sr, s21_strchr_suite());
  srunner_add_suite(sr, s21_strncmp_suite());
  srunner_add_suite(sr, s21_strncpy_suite());
  srunner_add_suite(sr, s21_strcspn_suite());
  srunner_add_suite(sr, s21_strpbrk_suite());
  srunner_add_suite(sr, s21_strlen_suite());
  srunner_add_suite(sr, s21_strstr_suite());
  srunner_add_suite(sr, s21_strerror_suite());
  srunner_add_suite(sr, s21_strrchr_suite());
  srunner_add_suite(sr, s21_to_upper_suite());
  srunner_add_suite(sr, s21_to_lower_suite());
  srunner_add_suite(sr, s21_trim_suite());
  srunner_add_suite(sr, s21_insert_suite());
  srunner_add_suite(sr, s21_strtok_suite());
  srunner_add_suite(sr, s21_sprintf_f_suite());
  srunner_add_suite(sr, s21_sprintf_c_suite());
  srunner_add_suite(sr, s21_sprintf_d_suite());
  srunner_add_suite(sr, s21_sprintf_s_suite());
  srunner_add_suite(sr, s21_sprintf_g_suite());
  srunner_add_suite(sr, s21_sprintf_e_suite());
  srunner_add_suite(sr, s21_sprintf_o_suite());
  srunner_add_suite(sr, s21_sprintf_u_suite());
  srunner_add_suite(sr, s21_sprintf_x_suite());
  srunner_add_suite(sr, s21_sprintf_n_suite());
  srunner_add_suite(sr, s21_sprintf_p_suite());
  srunner_add_suite(sr, s21_sprintf_combo_suite());
  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
