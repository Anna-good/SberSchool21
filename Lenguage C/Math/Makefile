CC = gcc
FLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck

ifeq ($(shell uname), Linux)
  LFLAGS += -pthread -lsubunit -lrt -lm
endif

all: clean test

test: s21_math.a
	$(CC) $(FLAGS) -c s21_math_test.c
	$(CC) s21_math_test.o $(FLAGS) $(LFLAGS) -L. s21_math.a -o test

s21_math.a:
	$(CC) $(FLAGS) -c s21_math.c 
	ar rc s21_math.a s21_math.o 
	ranlib s21_math.a

add_coverage:
	$(eval FLAGS += --coverage)

gcov_report: clean add_coverage test
	-./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

style_check:
	clang-format -n *.c *.h

style_fix:
	clang-format -i *.c *.h

clean: 
	rm -rf *.o *.a *.gcno *.gcda test test.info report

rebuild: clean all
