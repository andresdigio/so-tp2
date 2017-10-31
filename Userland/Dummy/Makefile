include ../Makefile.inc

MODULE=0002-dummy.bin
SOURCES=$(wildcard [^_]*.c)
LIB = $(wildcard ../Lib/*.o)

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -I../Lib/include -T dummy.ld _loader.c $(SOURCES) $(LIB) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print