# Makefile IAL Project
# Jindřich Šíma (xsimaj04), Marek Gergel (xgerge01)

PROG_NAME = graph_properties
# -g for debug , -O2 for optimization (0 - disabled, 1 - less, 2 - more)
CCFLAGS := -O0 -Wall -Wextra -std=c17 -pedantic
SRC_FILES := $(wildcard src/*.c)
HEADER_FILES := $(wildcard include/*.h)
OBJ_FILES := $(patsubst src/%.c,libs/%.o,$(SRC_FILES))
TEST_GRAPHS := $(wildcard testData/*)

.PHONY: all program run run-test clean zip

all: program

libs/%.o: src/%.c
	gcc $(CCFLAGS) -c $< -o $@

program: $(OBJ_FILES)
	gcc $(CCFLAGS) $^ -o $(PROG_NAME)

run:
	./$(PROG_NAME)

run-test:
	@for graph in $(TEST_GRAPHS); do printf "$${graph}\n"; ./$(PROG_NAME) < $${graph}; printf "\n"; done

clean:
	rm -rf $(PROG_NAME)*
	rm -rf libs/*.o

zip: clean
	zip -r $(PROG_NAME).zip include libs src testData Makefile dokumentace.pdf