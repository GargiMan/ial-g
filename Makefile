#Names....
CCFLAGS := -g -Wall -Wextra -std=c17 -O2 -pedantic
SRC_FILES := $(wildcard src/*.c)
HEADER_FILES := $(wildcard include/*.h)
OBJ_FILES := $(patsubst src/%.c,libs/%.o,$(SRC_FILES))

.PHONY: all program run clean

all: program run clean

libs/%.o: src/%.c
	gcc $(CCFLAGS) -DDEBUG -c $< -o $@

program: $(OBJ_FILES)
	gcc $(CCFLAGS) -DDEBUG $^ -o main

run:
	./main

clean:
	rm -f main
	rm -f libs/*.o
