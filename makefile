CC   = gcc
LIBS = -lm -ldl 
LIBSRASPI = -lm -ldl -lwiringPi
INCS =  
CFLAGS = $(INCS) -Wall -O3 
LDFLAGS :=
DESTDIR :=
PREFIX  := /usr/local
BINDIR  := /bin
DEST     = $(DESTDIR)$(PREFIX)$(BINDIR)

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
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) $(LDFLAGS)
endif



install: $(NPL)
	mkdir -p $(DEST)
	install -s  $(NPL) $(DEST)

uninstall:
	rm $(DEST)/npl
		
%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)
	

.PHONY: clean all

clean: 
	rm -f *.o
	rm npl
	
