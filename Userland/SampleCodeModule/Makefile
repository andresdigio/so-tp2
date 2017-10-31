include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
LIB = $(wildcard ../Lib/*.o)

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -I../Lib/include -T sampleCodeModule.ld _loader.c $(SOURCES) $(LIB) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print
