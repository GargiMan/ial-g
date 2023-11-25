# Makefile IAL Project
# Marek Gergel (xgerge01)

PROG_NAME = graph_properties
CC = gcc
# -g for debug , -O2 for optimization (0 - disabled, 1 - less, 2 - more)
CCFLAGS := -g -O0 -Wall -Wextra -std=c17 -pedantic
SRC_FILES := src/main.c src/error.c src/parser.c src/graph.c src/graph_properties.c
TEST_FILES := $(wildcard testData/*)

.PHONY: all run test clean zip

all: $(PROG_NAME)

$(PROG_NAME): $(SRC_FILES)
	$(CC) $(CCFLAGS) $(SRC_FILES) -o $@

run:
	./$(PROG_NAME)

test:
	@for graph in $(TEST_FILES); do printf "$${graph}\n"; ./$(PROG_NAME) < $${graph}; printf "\n"; done

clean:
	rm -rf $(PROG_NAME)*

zip: clean
	zip -r $(PROG_NAME).zip include src testData Makefile dokumentace.pdf