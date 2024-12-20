CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic

PROJECT_NAME := libS21_matrix
PROJECT_PATH := .
INSTALL_PATH := ../deplib
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
#TESTS_SOURCE = tests.c
UNAME_S := $(shell uname -s)
LIB_NAME := ${PROJECT_NAME}.a

ifeq ($(UNAME_S), Linux)
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread
endif
ifeq ($(UNAME_S), Darwin)
	ADD_LIB = -lcheck -lm -lpthread
endif

all: clean build

build: ${LIB_NAME}

${LIB_NAME}: ${SOURCES}
	@printf "\e[40;32m\n"
	@echo "----------------------------------------"
	@echo "       Build ${PROJECT_NAME} library       "
	@echo "----------------------------------------"
	@tput sgr0
	${CC} ${CFLAGS} -c ${SOURCES}
	ar rc $@ $(OBJECTS)
	ranlib $@
	rm -rf *.o
	@printf "\e[40;32m\n"
	@echo "-- Build ${PROJECT_NAME} complete --"
	@tput sgr0

tests: ${TESTS_SOURCE} clang
	${CC} -g ${SOURCE} ${TESTS_SOURCE} $(ADD_LIB) -o tests
	valgrind -s --leak-check=full --show-leak-kinds=all ./tests

lcov:
	ifeq ("", "$(shell PATH=$(PATH) which lcov)")
		$(error Need to install lcov)
	endif

gcov_report:
	${CC} -g --coverage ${SOURCE} ${TESTS_SOURCE} $(ADD_LIB) -o tests
	./tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	rm -rfd *.gcda *.gcno *.out tests

linter:
	@printf "\e[40;32m\n"
	@echo "----------------------------------------"
	@echo " Style test for ${PROJECT_NAME} library "
	@echo "----------------------------------------"
	@tput sgr0
	clang-format --style=Google -n ${SOURCES} ${HEADERS}
	@#cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c --std=c11 ${SOURCES} ${HEADERS}
	@printf "\e[40;32m\n"
	@echo "-- Style test for ${PROJECT_NAME} ended --"
	@tput sgr0

clean:
	@rm -rf *.o && rm -rf *.gcno
	@rm -rf *.a && rm -rf *.gcda
	@rm -rf *.info 
	@rm -rf *.gcov
	@rm -rf ./test
	@rm -rf ./gcov_report
	@rm -rf ./report/
	@rm -rf s21_test
	@rm -rf *.out
	@rm -rf .clang-format

.PHONY: all build clean lcov clang gcov_report test