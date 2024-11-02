SHELL := /bin/bash

CC := gcc
CFLAGS := -Wall -Werror -Wextra -x c -std=c11 -pedantic
LIB_FLAGS := -lncurses
TEST_FLAGS := -lcheck
PROJECT_NAME = "s21_maze"
UNAME_S := $(shell uname -s)

LIB_PATH := ./lib

EXEC_FILENAME := ${PROJECT_NAME}

# Linter tests
CSTYLE := clang-format
CSTYLE_FLAGS := --style=Google -n
CSTYLE_CORRECT := --style=Google -i
# ifeq ($(UNAME_S),Linux)
#     CCFLAGS += -D LINUX
# endif
# ifeq ($(UNAME_S),Darwin)
#     CCFLAGS += -D OSX
# endif

.PHONY: all install uninstall build tests clean linter dvi

.DEFAULT_GOAL: all

all: build

install:

uninstall:

build:
	${MAKE} -C ${LIB_PATH} $@

clean:
	${MAKE} -C ${LIB_PATH} $@

tests:
	${MAKE} -C ${LIB_PATH} $@

dvi:
	${MAKE} -C ${LIB_PATH} $@
	
clangi:
	${MAKE} -C ${LIB_PATH} $@