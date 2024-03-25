CC = gcc
FLAG = -Wall -Werror -Wextra
LFLAGS = -lcheck

ifeq ($(shell uname), Linux)
  LFLAGS += -pthread -lsubunit -lrt -lm
endif

all: clean test

test: s21_string.a
	$(CC) $(FLAG) -c s21_string_test.c
	$(CC) s21_string_test.o $(FLAG) $(LFLAGS) -L. s21_string.a -o test

s21_string.a:
	$(CC) $(FLAG) -c s21_sprintf.c 
	$(CC) $(FLAG) -c s21_string.c 
	ar rc s21_string.a s21_string.o s21_sprintf.o 
	ranlib s21_string.a

add_coverage:
	$(eval FLAG += --coverage)

gcov_report: clean add_coverage test
	-./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean: 
	rm -rf *.o *.a *.gcno *.gcda test test.info report

rebuild: clean all
