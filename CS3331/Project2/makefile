all: pmandel-2 mandelc

dump: pmandel-2 mandelcDump

watch: pmandel-2 mandelcSleep


pmandel-2: pmandel-2.o
	gcc -g -o pmandel-2 pmandel-2.o -lm

pmandel-2.o: pmandel-2.c
	gcc -g -c pmandel-2.c


mandelc: mandelc.o 
	gcc -g -o mandelc mandelc.o -lm

mandelcDump: mandelcDump.o
	gcc -g -o mandelc mandelc.o -lm

mandelcSleep: mandelcSleep.o
	gcc -g -o mandelc mandelc.o -lm

mandelc.o: mandelc.c
	gcc -g -c mandelc.c

mandelcDump.o: mandelc.c
	gcc -g -DDUMPPOINTS -c mandelc.c

mandelcSleep.o: mandelc.c
	gcc -g -DSLEEPINT -c mandelc.c


clean:
	rm mandelc pmandel-2 *.o *.ppm

ticlean:
	rm *~
