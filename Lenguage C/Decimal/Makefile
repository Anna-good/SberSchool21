CC = gcc
FLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck
SRC =s21*.c
OBJ =*.o


ifeq ($(shell uname), Linux)
  LFLAGS += -pthread -lsubunit -lrt -lm
endif

all: clean test

test: s21_decimal.a
	$(CC) $(FLAGS) -c decimal_test.c
	$(CC) decimal_test.o $(FLAGS) $(LFLAGS) -L. s21_decimal.a -o test

s21_decimal.a:
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs s21_decimal.a $(OBJ)
	ranlib s21_decimal.a

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
