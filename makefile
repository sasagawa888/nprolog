npl : main.o parser.o function.o builtin.o extension.o link.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o
	gcc  -O3 -Wall  main.o parser.o function.o builtin.o extension.o link.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o -o npl -lm -ldl
main.o : main.c npl.h
	gcc   -Wall -c main.c
parser.o : parser.c npl.h
	gcc  -O3 -Wall -c parser.c
function.o : function.c npl.h
	gcc  -O3 -Wall -c function.c
builtin.o : builtin.c npl.h
	gcc  -O3 -Wall -c builtin.c
extension.o : extension.c npl.h
	gcc  -O3 -Wall -c extension.c
link.o : link.c npl.h
	gcc  -O3 -Wall -c link.c	
data.o : data.c npl.h
	gcc  -O3 -Wall -c data.c
gbc.o : gbc.c npl.h
	gcc  -O3 -Wall -c gbc.c
cell.o : cell.c npl.h
	gcc  -O3 -Wall -c cell.c
error.o : error.c npl.h
	gcc  -O3 -Wall -c error.c
bignum.o : bignum.c npl.h
	gcc  -O3 -Wall -c bignum.c
compute.o : compute.c npl.h
	gcc  -O3 -Wall -c compute.c
edit.o : edit.c npl.h
	gcc  -O3 -Wall -c edit.c

.PHONY: clean
clean: -lm
	rm -f *.o
