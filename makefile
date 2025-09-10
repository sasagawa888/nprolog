.POSIX:
.DELETE_ON_ERROR:

USE_WIRINGPI ?= 0
USE_GPIO ?= 0
USE_FLTO ?= 0

CC   := gcc
LIBS := -lm -ldl -pthread
INCS :=
CFLAGS := $(INCS) -Wall -O3
DESTDIR :=
PREFIX  := /usr/local
BINDIR  := /bin
DEST    := $(DESTDIR)$(PREFIX)$(BINDIR)

CURSES_CFLAGS := $(shell command -v ncursesw6-config >/dev/null 2>&1 && ncursesw6-config --cflags || echo "")
CURSES_LIBS   := $(shell command -v ncursesw6-config >/dev/null 2>&1 && ncursesw6-config --libs || echo "-lncurses")


NPROLOG ?= $(CURDIR)
export NPROLOG

SHAREDIR ?= $(PREFIX)/share/nprolog
export SHAREDIR

NPL   := npl
EDLOG := edlog

ifeq ($(shell uname -n),raspberrypi)
ifeq ($(USE_WIRINGPI),1)
LIBS += -lwiringPi
endif
endif


ifeq  ($(shell uname -n),raspberrypi)
ifeq ($(USE_GPIO),1)
CFLAGS += -D__rpigpio__
LIBS += -lgpiod -lpigpio
endif
endif


ifeq ($(USE_FLTO),1)
CFLAGS += -flto
endif
ifeq ($(USE_GDB),1)
CFLAGS += -O0 -g
endif

NPL_OBJS := main.o \
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


EDLOG_OBJS := edlog.o syntax_highlight.o


SRC_PROLOG := library/opengl.pl \
	library/plot.pl \
	library/python.pl \
	library/tcltk.pl

OBJ_PROLOG := $(SRC_PROLOG:.pl=.o)


./library/%.o: ./library/%.pl $(NPL)
	echo "use_module(compiler),compile_file('./$<')." | ./$(NPL) -r
	touch $@

TARGETS := $(NPL) $(EDLOG)

all: $(TARGETS)


$(NPL): $(NPL_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


$(EDLOG): $(EDLOG_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CURSES_LIBS)

edlog.o: edlog.c edlog.h term.h
	$(CC) $(CFLAGS) -c $< $(CURSES_CFLAGS)


%.o: %.c npl.h
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: install
install: $(NPL) $(EDLOG)
	mkdir -p $(DEST)
	install -s $(NPL) $(DEST)
	install -s $(EDLOG) $(DEST)
	mkdir -p $(DESTDIR)$(SHAREDIR)
	install -m 644 library/* $(DESTDIR)$(SHAREDIR)


.PHONY: prolog
prolog: $(OBJ_PROLOG)

.PHONY: uninstall
uninstall:
	rm -f $(DEST)/$(NPL) $(DEST)/$(EDLOG)

# clean
.PHONY: clean all
clean:
	rm -f *.o $(NPL) $(EDLOG) $(OBJ_PROLOG)