CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -O0 -g
SRC = src/main.c src/pool_allocator.c src/baseline_malloc.c src/benchmark.c
OUT = allocator_test

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)