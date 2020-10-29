
CC   = gcc
LIBS = -lm -ldl 
LIBSRASPI = -lm -ldl -lwiringPi
INCS =  
CFLAGS = $(INCS) -Wall -O3 
DEST = /usr/local/bin

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
	install  $(NPL) $(DEST)

$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) 
	

raspi:	$(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBSRASPI) 
	install  $(NPL) $(DEST)

install:	$(NPL)
			install  $(NPL) $(DEST)

		
%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean all

clean: 
	rm -f *.o
	rm npl
