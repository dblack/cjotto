all: jotto 
jotto: jotto.o main.o jdict.o
	gcc -o jotto jotto.o main.o jdict.o

jotto.o: jotto.c jotto.h jdict.h
	gcc -c jotto.c

main.o: main.c jotto.h jdict.h
	gcc -c main.c

jdict.o: jdict.c jotto.h jdict.h
	gcc -c jdict.c

tests:	test/jotto.c
	gcc -o test/jotto test/jotto.c jotto.o jdict.o -L/usr/local/lib -lcunit 

test:	jotto tests
	test/jotto
