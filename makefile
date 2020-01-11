opl : main.o parser.o function.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o
	gcc  -O3 -Wall  main.o parser.o function.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o -o opl -lm -ldl
main.o : main.c opl.h
	gcc  -Wall -c main.c
parser.o : parser.c opl.h
	gcc -O3 -Wall -c parser.c
function.o : function.c opl.h
	gcc -O3 -Wall -c function.c
data.o : data.c opl.h
	gcc -O3 -Wall -c data.c
gbc.o : gbc.c opl.h
	gcc -O3 -Wall -c gbc.c
cell.o : cell.c opl.h
	gcc -O3 -Wall -c cell.c
error.o : error.c opl.h
	gcc -O3 -Wall -c error.c

bignum.o : bignum.c opl.h
	gcc -O3 -Wall -c bignum.c -lm -ldl

compute.o : compute.c opl.h
	gcc -O3 -Wall -c compute.c -lm -ldl

edit.o : edit.c opl.h
	gcc -O3 -Wall -c edit.c -lm -ldl

.PHONY: clean
clean: -lm
	rm -f opl *.o
