SHELL := /bin/bash

CC := gcc
CFLAGS := -Wall -Werror -Wextra -x c -std=c11 -pedantic -c
TEST_FLAGS := -lcheck
PROJECT_NAME = libS21_maze
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	TEST_LIB = -lcheck -lsubunit -lm -lrt -lpthread
endif
ifeq ($(UNAME_S), Darwin)
	TEST_LIB = -lcheck -lm -lpthread
endif

LIB_PATH := .
LIB_SOURCES_DIR := ${LIB_PATH}/sources
LIB_OBJECTS_DIR := ${LIB_PATH}/objects
LIB_NAME := ${PROJECT_NAME}.a
LIB_SOURCES := $(wildcard ${LIB_SOURCES_DIR}/*.c)
LIB_HEADERS := $(wildcard ${LIB_SOURCES_DIR}/*.h)
LIB_OBJECTS := $(patsubst %.c, %.o, $(LIB_SOURCES))
LIB_DEPENDANCY := ${LIB_PATH}/s21_matrix

CSTYLE := clang-format
CSTYLE_FLAGS := --style=Google -n
CSTYLE_CORRECT := --style=Google -i

C_CHECK = cppcheck
C_CHECK_FLAGS = --enable=all --force --suppress=missingIncludeSystem --language=c --std=c11

DOX_CONFIG = ./Doxyfile

.DEFAULT_GOAL: all

all: build dvi
.PHONY: all

install:
.PHONY: install

uninstall:
.PHONY: uninstall

build: dependancy ${LIB_NAME}
.PHONY: build

clean:
	${MAKE} -C ${LIB_DEPENDANCY} clean
	@rm -rf ./doc
	@rm -rf ${LIB_OBJECTS_DIR}
	@rm -f ${LIB_NAME}
.PHONY: clean


linter: ${CSTYLE}
	@printf "\e[40;32m\n"
	@echo "---------------------------------------"
	@echo "      Style tests for dependancies     "
	@echo "---------------------------------------"
	@tput sgr0
	@${MAKE} -C ${LIB_DEPENDANCY} linter
.PHONY: linter

tests: linter
.PHONY: tests

dvi:
	@echo "---------------------------------------"
	@echo " Documentation generation from sources "
	@echo "---------------------------------------"
	doxygen ${DOX_CONFIG}
.PHONY: dvi
	
${CSTYLE}: ${LIB_SOURCES} ${LIB_HEADERS}
	@printf "\e[40;32m\n"
	@echo "--------------------------------------"
	@echo " Style test for lib sources started "
	@echo "--------------------------------------"
	@tput sgr0
	$@ ${CSTYLE_FLAGS} $^
	@printf "\e[40;32m\n"
	@echo "-- Style test for ${PROJECT_NAME} sources ended --"
	@tput sgr0

clangi: ${LIB_SOURCES} ${LIB_HEADERS}
	${CSTYLE} ${CSTYLE_CORRECT} $^
.PHONY: clangi

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

dependancy:
	@printf "\e[40;32m\n"
	@echo "----------------------------------------"
	@echo "      Build & install dependancies      "
	@echo "----------------------------------------"
	@tput sgr0
	@${MAKE} -C ${LIB_DEPENDANCY} build
.PHONY: dependancy