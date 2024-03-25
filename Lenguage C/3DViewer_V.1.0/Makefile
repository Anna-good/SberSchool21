# Makefile version 0.3.5
# Author grettawa, dudeemik, lorriros
# 22/08/2023

CC 			:= gcc
STD			:= -std=c11
CFLAGS 		= $(STD) -Wall -Werror -Wextra
GCOV_FLAGS	:= --coverage
LCOV		:= lcov
QT_MAKER	:= qmake

PROJECT_DIR := 3DViewerV1.0

BACK_DIR	:= 3DViewerV1.0/back/
SOURCES 	= $(wildcard $(BACK_DIR)*.c)
OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))

FRONT_DIR	:= 3DViewerV1.0/front/
SOURCES_CPP = $(wildcard $(FRONT_DIR)*.cpp $(FRONT_DIR)MainWindow/*.cpp $(FRONT_DIR)OpenGl/*.cpp)
HEADERS = $(wildcard $(FRONT_DIR)MainWindow/*.h $(FRONT_DIR)OpenGl/*.h)

UTESTS_DIR	:= UTests/
UT_SOURCES	= $(wildcard $(UTESTS_DIR)*.c)
UT_OBJECTS	= $(patsubst %.c, %.o, $(UT_SOURCES))

BUILD_DIR	:= build/
PROJECT		:= 3DViewer1_0
STATIC_LIB	:= 3D_Viewer.a

# NAME OF PC CORE
UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S),Linux) # Linux
	OPEN_CMD		= xdg-open
	TEST_CHECK_F	= -lcheck -lsubunit
	ADD_LIB			= -lm -lrt -lpthread
endif
ifeq ($(UNAME_S),Darwin) # MacOS
	OPEN_CMD		= open
	TEST_CHECK_F	= $(shell pkg-config --cflags --libs check)
	ADD_LIB			=
endif

all: dist dvi gcov rebuild start

# 3D_Viewer.a objects or UTests objects
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -c

# 3D_Viewer.a create static library
$(STATIC_LIB): clean $(OBJECTS)
	ar -rcs $@ $(OBJECTS)
	ranlib $@
	@-rm -f $(BACK_DIR)*.o

create_obj: data-samples/cube.txt data-samples/deer.txt data-samples/drone_costum.txt
	cp data-samples/cube.txt data-samples/cube.obj
	cp data-samples/deer.txt data-samples/deer.obj
	cp data-samples/drone_costum.txt data-samples/drone_costum.obj
# UTests linking and start test
tests: clean create_obj $(STATIC_LIB) $(UT_OBJECTS)
	$(CC) $(CFLAGS) $(UT_SOURCES) -o test $(STATIC_LIB) $(TEST_CHECK_F) $(ADD_LIB)
	@-rm -f $(UTESTS_DIR)*.o
	./test

no_start_tests: clean create_obj $(STATIC_LIB) $(UT_OBJECTS)
	$(CC) $(CFLAGS) $(UT_SOURCES) -o test $(STATIC_LIB) $(TEST_CHECK_F) $(ADD_LIB)
	@-rm -f $(UTESTS_DIR)*.o

clean:
	rm -rf Documentation test gcov .clang-format
	rm -rf $(BACK_DIR)*.o $(UTESTS_DIR)*.o data-samples/*.obj *.a *.gcda *.gcno *.gch *.pdf *.tar rep.info test.info test.dSYM report.info

dvi:
	rm -rf Documentation
	doxygen
	$(OPEN_CMD) Documentation/html/index.html

dist: clean uninstall
	rm -rf $(PROJECT)_archive
	mkdir $(PROJECT)_archive
	mkdir $(PROJECT)_archive/src
	cp -R ../*.md Makefile UTests Doxyfile $(PROJECT_DIR) $(PROJECT)_archive/src
	tar cvzf $(PROJECT)_archive.tar $(PROJECT)_archive/
	rm -rf $(PROJECT)_archive

rebuild: uninstall install

# start 3DViewerV1.0
start:
ifeq ($(UNAME_S),Linux) # Linux
	./../$(BUILD_DIR)$(PROJECT)
endif
ifeq ($(UNAME_S),Darwin) # MacOS
	./../$(BUILD_DIR)$(PROJECT).app/Contents/MacOS/$(PROJECT)
endif

install:
	rm -rf ../build
	mkdir -vp ../build
	cd ../build && cmake ../src/3DViewerV1.0
	cd ../build && $(MAKE)
	rm -rf $(BUILD_DIR)*.o
	rm -rf $(PATH_BACK)*.o

uninstall:
	rm -rf 3DViewerV1.0/CMakeLists.txt.user
	rm -rf ../build
	rm -rf install

set_gcov_flags:
	$(eval CFLAGS += $(GCOV_FLAGS))

gcov: clean set_gcov_flags tests
	mkdir -p gcov
	$(LCOV) --capture --directory . --output-file report.info
	genhtml report.info --output-directory gcov
	rm -rf $(BACK_DIR)*.gcno $(BACK_DIR)*.gcda $(BACK_DIR)*.gcov $(UTESTS_DIR)*.gcda $(UTESTS_DIR)*.gcno $(UTESTS_DIR)*.gcov *.gcno *.gcda *.gcov
	$(OPEN_CMD) gcov/index.html

# *======================*
# Additional targets

check-leaks: no_start_tests
ifeq ($(UNAME_S),Linux) # Linux
	valgrind -s --trace-children=yes -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif
ifeq ($(UNAME_S),Darwin) # MacOS
	leaks --atExit -- ./test
endif

valgrind: no_start_tests
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

# static analysis (static means before compilation)
# better than gcc flags -Wall -Werror -Wextra
cppcheck:
	cppcheck ./ --enable=all

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(SOURCES) $(UT_SOURCES) $(BACK_DIR)*.h $(SOURCES_CPP) $(HEADERS)
	rm .clang-format

# !!!if use with git you should format and commit before you want to work
# style that you want to use can be sets by option --style="name" but
# if you have file .clang-format you can use it to set style format
fix-style:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(SOURCES) $(UT_SOURCES) $(BACK_DIR)*.h $(SOURCES_CPP) $(HEADERS)
	rm .clang-format

# ubuntu
download_libs:
# for GIF
	sudo apt install libgif-dev
# for Qt6
	sudo apt install qt6-base-dev
# gcov - утилита для генерации файлов .gcda .gcno, хранящих информацию о покрытии кода после запуска программы
# вместо ее прямого использования в данном случае мы применяем флаги gcov для утилиты gcc
# такие как --coverage или --fprofile-arcs и --ftest-coverage
# оба они выдают необходимые нам файлы .gcda .gcno при компиляции вместе с объектниками

# lcov — графический интерфейс для gcov
# Он собирает файлы gcov для нескольких файлов с исходниками и создает комплект HTML-страниц с кодом и сведениями
# о уровне покрытия кода

# ЦЕЛИ:
# Основные: all, clean, tests, gcov_report, dvi, dist, install, uninstall

# ЗАВИСИМОСТИ:
# То без чего цель не может быть исполнена
# Забавный факт: при указании в качестве зависимости имена файлов с .o
# make будет искать исходники с расширением .c
# и если найдет, то начнет делать объектные файлы "gcc -c -o a.c a.o"
# Затем произведет их линковку "gcc a.o -o a.out"
# Однако в данном Makefile мы не используем эту особенность из-за необходимости
# подвергать файлы статическому анализу (-Wall -Werror -Wextra) на уровне препроцессора (до компиляции)
# Пример синтаксиса:
# 3DViewer.a: s21_file.o
# *====================*
# Неявные действия:
# gcc -c -o s21_file.o s21_file.c
# gcc s21_file.o -o 3DViewer.a

# УСЛОВИЯ:
# Основное назначение, как понятно из названия - проверить необходимое для нас соответствие
# В данном Makefile'е они используются для проверки ядра операционной системы, чтобы
# запустить исполнение подходящих инструкций
# Пример синтаксиса:
#	ifeq (value1, value2)
#		instruction1
#		...
#		instructionN
#	endif

# ПЕРЕМЕННЫЕ:
# Хранят необходимые для нас значения (только числа и строки)
# Определяются вне целей
# Могут быть константами при использовании соответствующего оператора присваивания ":="
# Для извлечения значений используются: знак доллара и скобки - "$(VARIABLE)"
