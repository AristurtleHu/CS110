CC = gcc
CFLAGS = -O0 
all : base_test fast_test

clean:
	@-rm -f *.o log_base log_fast
	
base:
	@-rm -f *.o log_base
	$(CC) $(CFLAGS) -o log_base log_base.c 

fast:
	@-rm -f *.o log_fast
	$(CC) $(CFLAGS) -o log_fast log_fast.c $(LIBS)

base_test: base
	./log_base 

fast_test: fast
	./log_fast


 