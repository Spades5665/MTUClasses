calc: main.o expr.o scanner.o parser.o
	gcc main.o expr.o scanner.o parser.o -o calc -lm

%.o: %.c *.h
	gcc -Wall -c $< -o $@

scanner.c: calc.flex parser.h
	flex -oscanner.c calc.flex

parser.c parser.h: calc.bison
	bison --defines=parser.h --output=parser.c -v calc.bison

clean:
	rm -f parser.* parser.output scanner.c *.o calc

cleanOut:
	rm *.out
