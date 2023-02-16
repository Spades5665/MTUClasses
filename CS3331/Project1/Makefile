all:pmandel

pmandel: pmandel.o
	gcc pmandel.o -o pmandel -lm -D COLORSCHEME=1

#mandel: mandel.o
#	gcc mandel.o -o mandel -lm -D COLORSCHEME=1

pmandel.o: pmandel.c
	gcc -c pmandel.c

#mandel.o: mandel.c
#	gcc -c mandel.c

clean:
	rm *.ppm
	rm *.o
	rm pmandel
#	rm mandel