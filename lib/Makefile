SHELL := /bin/bash

CC := gcc
CFLAGS := -Wall -Werror -Wextra -x c -std=c11 -pedantic -c
TEST_FLAGS := -lcheck
PROJECT_NAME = s21_maze
UNAME_S := $(shell uname -s)

LIB_PATH := .
LIB_SOURCES_DIR := ${LIB_PATH}/sources
LIB_OBJECTS_DIR := ${LIB_PATH}/objects
LIB_NAME := ${PROJECT_NAME}_lib.a
LIB_SOURCES := $(wildcard ${LIB_SOURCES_DIR}/*.c)
LIB_HEADERS := $(wildcard ${LIB_SOURCES_DIR}/*.h)
LIB_OBJECTS := $(patsubst %.c, %.o, $(LIB_SOURCES))

CSTYLE := clang-format
CSTYLE_FLAGS := --style=Google -n
CSTYLE_CORRECT := --style=Google -i

C_CHECK = cppcheck
C_CHECK_FLAGS = --enable=all --force --suppress=missingIncludeSystem --language=c --std=c11

DOX_CONFIG = ./Doxyfile


.PHONY: all install uninstall build tests clean linter dvi clangi

.DEFAULT_GOAL: all

all: build dvi

install:

uninstall:

build: ${LIB_NAME}

clean:
	@rm -rf ./doc
	@rm -rf ${LIB_OBJECTS_DIR}
	@rm -f ${LIB_NAME}

linter: ${CSTYLE}

tests: linter

dvi:
	@echo "---------------------------------------"
	@echo " Documentation generation from sources "
	@echo "---------------------------------------"
	doxygen ${DOX_CONFIG}
	
${CSTYLE}: ${LIB_SOURCES} ${LIB_HEADERS}
	@echo "--------------------------------------"
	@echo " Style test for lib sources started "
	@echo "--------------------------------------"
	$@ ${CSTYLE_FLAGS} $^
	@echo "--------- Style test ended -----------"

clangi: ${LIB_SOURCES} ${LIB_HEADERS}
	${CSTYLE} ${CSTYLE_CORRECT} $^

${C_CHECK}: ${LIB_SOURCES} ${LIB_HEADERS}
	$@ ${C_CHECK_FLAGS} $^

${LIB_OBJECTS_DIR}:
	@mkdir $@

%.o: %.c
	@${CC} ${CFLAGS} -o $(addprefix ${LIB_OBJECTS_DIR}/, $(notdir $@)) $<

${LIB_NAME}: ${LIB_OBJECTS_DIR} ${LIB_OBJECTS}
	@echo "---------------------------------------"
	@ar rc $@ $(addprefix ${LIB_OBJECTS_DIR}/, $(notdir ${OBJECTS_LIB}))
	@ranlib $@
	@rm -rf ${LIB_OBJECTS}
	@echo "---------------------------------------"
	@echo " ${LIB_NAME} compilation complete"
	@echo "---------------------------------------"