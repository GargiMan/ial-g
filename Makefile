#Names....
CCFLAGS := -Wall -Wextra -std=c17 -O2 -pedantic
SRC_FILES := $(wildcard src/*.c)
HEADER_FILES := $(wildcard include/*.h)
OBJ_FILES := $(patsubst src/%.c,libs/%.o,$(SRC_FILES))
LIB_FILES := $(patsubst libs/%.o,libs/%.lib,$(OBJ_FILES))

all: program program programRun packing
.PHONY: all


libs/%.o: src/%.c
	g++ $(CCFLAGS) -DDEBUG -c $< -o $@

program: $(OBJ_FILES) 
	g++ $(CCFLAGS) -DDEBUG $^ -o program.exe

libs/%.lib: libs/%.o
	ar rcs ./$(basename $^).lib $^
	
packing: $(LIB_FILES)
	del .\libs\*.o
	del .\libs\main.lib

programRun:
	.\program.exe




