# Makefile IAL Project
# Marek Gergel (xgerge01)

PROG_NAME = graph_properties
CC = gcc
# -g for debug , -O2 for optimization (0 - disabled, 1 - less, 2 - more)
CCFLAGS := -g -O0 -Wall -Wextra -std=c17 -pedantic
SRC_FILES := $(wildcard src/*.c)
HEADER_FILES := $(wildcard include/*.h)
OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ_FILES := $(OBJ_FILES:src/%=libs/%)
TEST_FILES := $(wildcard testData/*)

.PHONY: all run run-test clean zip

all: $(PROG_NAME)

libs/%.o: src/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PROG_NAME): $(OBJ_FILES)
	$(CC) $(CCFLAGS) $^ -o $@

run:
	./$(PROG_NAME)

run-test:
	@for graph in $(TEST_FILES); do printf "$${graph}\n"; ./$(PROG_NAME) < $${graph}; printf "\n"; done

clean:
	rm -rf $(PROG_NAME)* $(OBJ_FILES)

zip: clean
	zip -r $(PROG_NAME).zip include libs src testData Makefile dokumentace.pdf