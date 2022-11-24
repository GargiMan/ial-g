# Makefile IAL Project
# All (replace)

PROG_NAME = graph_properties
CCFLAGS := -g -Wall -Wextra -std=c17 -O2 -pedantic
SRC_FILES := $(wildcard src/*.c)
HEADER_FILES := $(wildcard include/*.h)
OBJ_FILES := $(patsubst src/%.c,libs/%.o,$(SRC_FILES))
TEST_GRAPHS := $(wildcard testData/*)

.PHONY: all program run clean

all: program

libs/%.o: src/%.c
	gcc $(CCFLAGS) -DDEBUG -c $< -o $@

program: $(OBJ_FILES)
	gcc $(CCFLAGS) -DDEBUG $^ -o $(PROG_NAME)

run:
	./$(PROG_NAME)

run-test:
	@for graph in $(TEST_GRAPHS); do ./$(PROG_NAME) < $${graph}; done

clean:
	rm -f $(PROG_NAME)
	rm -f libs/*.o
