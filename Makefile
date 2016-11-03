#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: cellp cella

cellp: cellp.o memcheck.o
	$(CC) cellp.o memcheck.o -o cellp

cella: cella.o memcheck.o
	$(CC) cella.o memcheck.o -o cella

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

cellp.o: cellp.c memcheck.h
	$(CC) $(CFLAGS) -c cellp.c
cella.o: cella.c memcheck.h
	$(CC) $(CFLAGS) -c cella.c

testp:
	./cellp 60 60
testa: 
	./cella 60 60    
check:
	./c_style_check cellp.c cella.c

clean:
	rm -f *.o cellp cella
	


