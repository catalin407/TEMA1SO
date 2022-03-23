CC = gcc
CFLAGS = -Wall -Wextra -g

.PHONY: all clean

build: utilfunc.o so-cpp.o
	gcc -g -Wall utilfunc.o so-cpp.o -o so-cpp

so-cpp.o: so-cpp.c
	gcc -g -c so-cpp.c

utilfunc.o: utilfunc.c
	gcc -g -c utilfunc.c

clean:
	rm -f *.o so-cpp