#Names....
CCFLAGS := -g -Wall -Wextra -std=c17 -O2 -pedantic
SRC_FILES := $(wildcard src/*.c)
HEADER_FILES := $(wildcard include/*.h)
OBJ_FILES := $(patsubst src/%.c,libs/%.o,$(SRC_FILES))
LIB_FILES := $(patsubst libs/%.o,libs/%.lib,$(OBJ_FILES))

.PHONY: all program run packing

all: program packing run 

libs/%.o: src/%.c
	gcc $(CCFLAGS) -DDEBUG -c $< -o $@

program: $(OBJ_FILES)
	gcc $(CCFLAGS) -DDEBUG $^ -o main

libs/%.lib: libs/%.o
	ar rcs ./$(basename $^).lib $^

packing: $(LIB_FILES)
	rm -rf ./libs/*.o
	rm -rf ./libs/main.lib

run:
	./main




