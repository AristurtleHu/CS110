CC=gcc
CFLAGS=-Wpedantic -Wall -Wextra -Wvla -Werror -std=c11 -g -O0

MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes

OBJ=queue.o main.o
PRODUCT=lab2

all: $(PRODUCT)

$(PRODUCT): $(OBJ)
	$(CC) -o $(PRODUCT) $(OBJ)

# How this rule knows to compile vector.c and main.c?
# If there is another .c file, will this rule compiles that file?
.c.o:
	$(CC) -c $(CFLAGS) $<

memcheck: $(PRODUCT) # What if we don't write $(PRODUCT) here?
	$(MEMCHECK) ./$(PRODUCT)

clean:
	rm -rf $(OBJ) $(PRODUCT)
