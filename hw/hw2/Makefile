CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2 -ggdb

.PHONY: test clean
.SILENT: test

test: convert
	./convert < testcases/total-input.txt > testcases/total-output.txt
	python3 check.py testcases/total-output.txt testcases/total-answer.hash > testcases/total-output.mark
	tail -n 1 testcases/total-output.mark

convert: convert.c
	$(CC) $(CFLAGS) convert.c -o convert

clean:
	rm -f convert testcases/total-output.*