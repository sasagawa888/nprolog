opl : main.o parser.o function.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o
	gcc  -O4 -Wno-pointer-to-int-cast -Wall  main.o parser.o function.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o -o opl -lm -ldl
main.o : main.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c main.c -lm
parser.o : parser.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c parser.c -lm
function.o : function.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c function.c -lm -ldl
data.o : data.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c data.c -lm
gbc.o : gbc.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c gbc.c -lm
cell.o : cell.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c cell.c -lm
error.o : error.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c error.c -lm

bignum.o : bignum.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c bignum.c -lm

compute.o : compute.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c compute.c -lm

edit.o : edit.c opl.h
	gcc -O4 -Wno-pointer-to-int-cast -Wall -c edit.c -lm

.PHONY: clean
clean: -lm
	rm -f opl *.o
