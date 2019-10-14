CFLAGS=-std=gnu++98 -pedantic -Wall
myCode: code.o
	g++ -o myCode code.o
%.o : %.cpp
	gcc $(CFLAGS) -cpp $< 
.PHONY: clean
clean:
	rm -f code *.o *.cpp~ *.h~
