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
CURSES_CFLAGS := $(shell ncursesw6-config --cflags)
CURSES_LIBS := $(shell ncursesw6-config --libs)

NPL = npl
EDLIS = edlis

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
	edit.o \
	syntax_highlight.o

EDLIS_OBJS = edlis.o syntax_highlight.o

ifeq  ($(shell uname -n),raspberrypi)
all: $(NPL_OBJS) $(NPL)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBSRASPI)
else
all: $(NPL_OBJS) $(NPL) $(EDLIS)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) $(LDFLAGS)
endif

#$(EDLIS): $(EDLIS_OBJS)
#	$(CC) $(LDFLAGS) $^ -o $@ $(CURSES_LIBS)

#edlis.o: edlis.c edlis.h term.h
#	$(CC) $(CFLAGS) -c edlis.c

install: $(NPL) #$(EDLIS)
	mkdir -p $(DEST)
	install -s $(NPL) $(DEST)
#	install -s $(EDLIS) $(DEST)

uninstall:
	rm -f $(DEST)/npl $(DEST)/edlis

%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean all

clean: 
	rm -f *.o $(NPL) $(EDLIS)


