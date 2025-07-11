.PHONY: all run clean

CC=gcc
CFLAGS=-Iinclude
SRC=$(wildcard src/*.c)
TARGET=build/$(notdir $(CURDIR))

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
