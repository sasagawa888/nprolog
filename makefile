.POSIX:
.DELETE_ON_ERROR:

USE_WIRINGPI ?= 0
USE_FLTO ?= 0

CC   = gcc
LIBS = -lm -ldl -pthread 
INCS =  
CFLAGS = $(INCS) -Wall -O3 
DESTDIR :=
PREFIX  := /usr/local
BINDIR  := /bin
DEST     = $(DESTDIR)$(PREFIX)$(BINDIR)
CURSES_CFLAGS := $(shell ncursesw6-config --cflags)
CURSES_LIBS := $(shell ncursesw6-config --libs)

NPL = npl
EDLOG = edlog

ifeq  ($(shell uname -n),raspberrypi)
	ifeq ($(USE_WIRINGPI),1)
		LIBS += -lwiringPi
	endif
endif

ifeq ($(USE_FLTO),1)
	CFLAGS += -flto
endif 

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

# Files in library/ that need to be compiled 
SRC_PROLOG := library/opengl.pl \
	library/plot.pl \
	library/python.pl \
	library/tcltk.pl

OBJ_PROLOG := $(SRC_PROLOG:.pl=.o) 
./library/%.o: ./library/%.pl npl
	echo "use_module(compiler),compile_file('./$<')." | ./npl -r
	touch $@

all: $(NPL_OBJS) $(NPL) $(EDLOG)
$(NPL): $(NPL_OBJS)
	$(CC) $(NPL_OBJS) -o $(NPL) $(LIBS) $(CFLAGS)


$(EDLOG): $(EDLOG_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(CURSES_LIBS)

edlog.o: edlog.c edlog.h term.h
	$(CC) $(CFLAGS) -c edlog.c $(CURSES_CFLAGS)

.PHONY:install
install: $(NPL) $(EDLOG) 
	mkdir -p $(DEST)
	install -s $(NPL) $(DEST)
	install -s $(EDLOG) $(DEST)

.PHONY:prolog
prolog: $(OBJ_PROLOG)

.PHONY:uninstall
uninstall:
	rm -f $(DEST)/npl $(DEST)/edlog

%.o: %.c npl.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean all

clean: 
	rm -f *.o $(NPL) $(EDLOG) $(OBJ_PROLOG)


