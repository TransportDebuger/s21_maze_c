SHELL := /bin/bash

CC := gcc
CFLAGS := -Wall -Werror -Wextra -x c -std=c11 -pedantic -c
TEST_FLAGS := -lcheck
PROJECT_NAME = libs21_maze
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

CSTYLE := clang-format
CSTYLE_CORRECT := --style=Google -i

C_CHECK = cppcheck
C_CHECK_FLAGS = --enable=all --force --suppress=missingIncludeSystem --suppress=unusedFunction --language=c --std=c11

DOX_CONFIG = ./Doxyfile

.DEFAULT_GOAL: all

all: build dvi
.PHONY: all

install:
.PHONY: install

uninstall:
.PHONY: uninstall

build: ${LIB_NAME}
.PHONY: build

clean:
	@rm -rf ./doc
	@rm -rf ${LIB_OBJECTS_DIR}
	@rm -f ${LIB_NAME}
.PHONY: clean


linter: ${CSTYLE} ${C_CHECK}
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
	@cp ../../materials/linters/.clang-format .
	@printf "\e[40;32m\n";
	@echo '--- Style test for "${PROJECT_NAME}" started ---'
	@for src in ${LIB_SOURCES} ${LIB_HEADERS} ; do \
		var=`"$@" "${LIB_PATH}/$$src" | diff "${LIB_PATH}/$$src" - | wc -l` ; \
		if [ $$var -ne 0 ] ; then \
		    printf "\e[40;31m\n"; \
			echo "$$src style test [FAULT] (diff: $$var lines)." ; \
			tput sgr0; \
			exit 1 ; \
		else \
			echo "$$src style test [PASS]"; \
		fi ; \
	done
	@rm -f ./.clang-format
	@echo '--- Style check for "${PROJECT_NAME}" PASSED ---'
	@tput sgr0

clangi: ${LIB_SOURCES} ${LIB_HEADERS}
	${CSTYLE} ${CSTYLE_CORRECT} $^
.PHONY: clangi

${C_CHECK}: ${LIB_SOURCES} ${LIB_HEADERS}
	@printf "\e[40;32m\n";
	@echo '--- $@ test for "${PROJECT_NAME}" started ---' 
	$(eval ERR_OUTPUT := $(shell $@ ${C_CHECK_FLAGS} $^ 2>&1 | grep -v -e done -e Checking))
	@if [ -n "$(ERR_OUTPUT)" ]; then \
  		printf "\e[40;31m\n"; \
		echo "Warrnings and errors present!"; \
  		echo "$(ERR_OUTPUT)"; \
		echo "--- $@ test for "${PROJECT_NAME}" FAULT ---"; \
		tput sgr0; \
  		exit 1; \
	else \
  		echo "--- $@ test for "${PROJECT_NAME}" PASSED ---"; \
 	fi

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