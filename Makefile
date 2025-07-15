.PHONY: all run clean

CC=gcc
CFLAGS=-Iinclude -Wall -Wextra
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)
TARGET=build/tiny-shell

all: $(TARGET)

build:
	mkdir -p build

$(TARGET): build $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build

