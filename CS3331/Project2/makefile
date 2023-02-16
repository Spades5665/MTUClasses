all: pmandel-2 mandelc

pmandel-2: pmandel-2.o iterMap.o iterSpectrumMap.o spectrumToRGB.o 
	gcc -g -o pmandel-2 pmandel-2.o iterMap.o iterSpectrumMap.o spectrumToRGB.o -lm

mandelc: mandelc.o 
	gcc -g -o mandelc mandelc.o -lm

pmandel-2.o: pmandel-2.c
	gcc -g -c pmandel-2.c

mandelc.o: mandelc.c
	gcc -g -c mandelc.c

iterMap.o: iterMap.c
	gcc -g -c iterMap.c

iterSpectrumMap.o: iterSpectrumMap.c
	gcc -g -c iterSpectrumMap.c

spectrumToRGB.o: spectrumToRGB.c
	gcc -g -c spectrumToRGB.c

clean:
	rm mandelc pmandel-2 *.o *.ppm

ticlean:
	rm *~
