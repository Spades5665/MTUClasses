all: pmandel-2 mandelc

dump: pmandel-2 mandelcDump

pmandel-2: pmandel-2.o
	gcc -g -o pmandel-2 pmandel-2.o -lm

mandelc: mandelc.o 
	gcc -g -o mandelc mandelc.o -lm

mandelcDump: mandelc.o
	gcc -g -DDUMPPOINTS -o mandelc mandelc.c -lm

pmandel-2.o: pmandel-2.c
	gcc -g -c pmandel-2.c

mandelc.o: mandelc.c
	gcc -g -c mandelc.c

clean:
	rm mandelc pmandel-2 *.o *.ppm

ticlean:
	rm *~
