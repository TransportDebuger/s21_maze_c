SHELL := /bin/bash

CC := gcc
CFLAGS := -Wall -Werror -Wextra -x c -std=c11 -pedantic
LIB_FLAGS := -lncurses
TEST_FLAGS := -lcheck
PROJECT_NAME = s21_maze
UNAME_S := $(shell uname -s)

LIB_PREFIX := lib
LIB_PATH := ./${LIB_PREFIX}

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

all: build dvi

install:

uninstall:

build:
	${MAKE} -C ${LIB_PATH} $@

clean:
	${MAKE} -C ${LIB_PATH} $@

linter:
	@printf "\e[40;32m\n"
	@echo "---------------------------------------"
	@echo "  Style tests for projects ${PROJECT_NAME}   "
	@echo "---------------------------------------"
	@tput sgr0
	${MAKE} -C ${LIB_PATH} $@
	@printf "\e[40;32m\n"
	@echo "-- Style tests for project ${PROJECT_NAME} ended --"
	@tput sgr0

tests:
	${MAKE} -C ${LIB_PATH} $@

dvi:
	${MAKE} -C ${LIB_PATH} $@
	
clangi:
	${MAKE} -C ${LIB_PATH} $@