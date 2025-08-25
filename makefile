CC   = gcc
LIBS = -lm -ldl -pthread -lcurl
LIBSRASPI = -lm -ldl -lwiringPi -pthread -lcurl
INCS =  
CFLAGS = $(INCS) -Wall -O3 -flto
LDFLAGS :=
DESTDIR :=
PREFIX  := /usr/local
BINDIR  := /bin
DEST     = $(DESTDIR)$(PREFIX)$(BINDIR)
CURSES_CFLAGS := $(shell ncursesw6-config --cflags)
CURSES_LIBS := $(shell ncursesw6-config --libs)

NPL = npl
EDLOG = edlog

NPL_OBJS = main.o \
	parser.o \
	function.o \
	builtin.o \
	extension.o \
	parallel.o \
	superset.o \
	link.o \
	data.o \
	gbc.o \
	cell.o \
	error.o \
	bignum.o \
	compute.o \
	clp.o \
	edit.o \
	syntax_highlight.o

EDLOG_OBJS = edlog.o syntax_highlight.o

ifeq  ($(shell uname -n),raspberrypi)
all: $(NPL_OBJS) $(NPL)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBSRASPI)
else
all: $(NPL_OBJS) $(NPL) $(EDLOG)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) $(LDFLAGS)
endif

$(EDLOG): $(EDLOG_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(CURSES_LIBS)

edlog.o: edlog.c edlog.h term.h
	$(CC) $(CFLAGS) -c edlog.c $(CURSES_CFLAGS)

install: $(NPL) $(EDLOG)
	mkdir -p $(DEST)
	install -s $(NPL) $(DEST)
	install -s $(EDLOG) $(DEST)

uninstall:
	rm -f $(DEST)/npl $(DEST)/edlog

%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean all

clean: 
	rm -f *.o $(NPL) $(EDLOG)


