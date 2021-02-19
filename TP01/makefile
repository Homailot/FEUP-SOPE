clean:
	rm -f tp01_01 tp01_03 tp01_04 tp01_04_static tp01_05 tp01_06 tp01_10 tp01_11a tp01_11ac tp01_11b tp01_12

tp01_01: tp01_01.c
	clang -MJ tp01_01.json -Wall tp01_01.c -o tp01_01

tp01_03: tp01_03.c 
	clang -MJ tp01_03.json -Wall tp01_03.c -o tp01_03

tp01_04: tp01_04.c 
	clang -MJ tp01_04.json -Wall tp01_04.c -o tp01_04

tp01_04.o: tp01_04.c 
	clang -MJ tp01_04.json -c -Wall tp01_04.c -o tp01_04.o

tp01_04_static: tp01_04.o
	clang -o tp01_04_static tp01_04.o -static

tp01_05: tp01_05.c 
	clang -MJ tp01_05.json -Wall tp01_05.c -o tp01_05

tp01_06: tp01_06.c 
	clang -MJ tp01_06.json -Wall tp01_06.c -o tp01_06

tp01_10: tp01_10.c 
	clang -MJ tp01_10.json -Wall tp01_10.c -o tp01_10
	
tp01_11ac: tp01_11ac.c 
	clang -MJ tp01_11ac.json -Wall tp01_11ac.c -o tp01_11ac

tp01_11b: tp01_11b.c 
	clang -MJ tp01_11b.json -Wall tp01_11b.c -o tp01_11b

tp01_12: tp01_12.c 
	clang -MJ tp01_12.json -Wall tp01_12.c -o tp01_12

hello_time: tp01_10
	time ./tp01_10
