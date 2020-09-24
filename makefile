
CC   = gcc
LIBS = -lm -ldl 
INCS =  
CFLAGS = $(INCS) -Wall -O3 

NPL = npl

NPL_OBJS = main.o \
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

all: $(NPL_OBJS) $(NPL)

$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) 
		
%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean all

clean: 
	rm -f *.o
	rm npl
