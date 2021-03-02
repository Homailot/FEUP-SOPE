clean:
	rm -f tp02_05a tp02_05b tp02_08 tp02_09 tp02_10

tp02_05a: tp02_05a.c
	clang -MJ tp02_05a.json -Wall tp02_05a.c -o tp02_05a

tp02_05b: tp02_05b.c
	clang -MJ tp02_05b.json -Wall tp02_05b.c -o tp02_05b

tp02_08: tp02_08.c
	clang -MJ tp02_08.json -Wall tp02_08.c -o tp02_08

# Makefile for very simple example Posix threads usage
# The executable built is:
#	sthread
#
CC = clang
CFLAGS = -Wall
LIBS = -lpthread

tp02_09: tp02_09.c
	$(CC) -MJ tp02_09.json -o tp02_09 -g tp02_09.c $(LIBS)


tp02_10: tp02_10.c
	$(CC) -MJ tp02_10.json -o tp02_10 -g tp02_10.c $(LIBS)
