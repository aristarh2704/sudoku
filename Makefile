CCFLAGS=`pkg-config gtk+-2.0 --cflags`
LDFLAGS=`pkg-config gtk+-2.0 --libs`
all: gdk
core/sudoku.o: core/sudoku.c sudoku.h
	tcc -c -I. core/sudoku.c -o core/sudoku.o
gdk.o: gdk.c sudoku.h
	tcc $(CCFLAGS) -c gdk.c -o gdk.o
gdk: gdk.o core/sudoku.o
	tcc $(LDFLAGS) gdk.o core/sudoku.o -s -o sudoku