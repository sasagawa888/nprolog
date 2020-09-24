
CC   = gcc
LIBS = -lm -ldl 
INCS =  
CFLAGS = $(INCS) -Wall -O3 

NPL = npl

NPL_OBJS : main.o \
	parser.o \
	function.o \
	builtin.o \
	extension.o \
	link.o \
	data.o \
	gbc.o \
	cell.o \
	error.o \
	bignum.o \
	compute.o \
	edit.o

.PHONY: all clean

all: $(NPL)	
		
%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(NPL): $(NPL_OBJ)
	$(CC) $(NPL_OBJ) -o $(NPL) $(LIBS) 

clean: -lm
	rm -f *.o
