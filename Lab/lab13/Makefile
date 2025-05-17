CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -fopenmp -lm
EXECUTABLES = hello matmul pi mergesort

all: $(EXECUTABLES)

% : %.o
	$(CC) $(CFLAGS) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(EXECUTABLES) *.o

.PHONY: all clean