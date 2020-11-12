
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




ifeq  ($(shell uname -n),raspberrypi)
all: $(NPL_OBJS) $(NPL)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBSRASPI) 
else
all: $(NPL_OBJS) $(NPL)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) 
endif



install: $(NPL)
	install -s  $(NPL) $(DEST)
	mkdir -p /home/nprolog
	cp jump.h /home/nprolog
	cp library/compiler.pl /home/nprolog
	cp library/dcg.pl /home/nprolog

uninstall:
	rm $(DEST)/npl
	rm /home/nprolog/*.*
	rmdir /home/nprolog
		
%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)
	

.PHONY: clean all

clean: 
	rm -f *.o
	rm npl
