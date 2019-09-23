CFLAGS=-std=gnu99 -pedantic -Wall
breaker: breaker.o
	gcc - o myProgram breaker.o
%.o : %.c
	gcc $(CFLAGS) -c $< 
.PHONY: clean
clean:
	rm -f myProgram *.o *.c~ *.h~
