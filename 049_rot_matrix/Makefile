CFLAGS=-std=gnu99 -pedantic -Wall
rotateMatrix: rotateMatrix.o
	gcc -o rotateMatrix rotateMatrix.c
%.o : %.c
	gcc $(CFLAGS) -c $< 
.PHONY: clean
clean:
	rm -f rotateMatrix *.o *.c~ *.h~
