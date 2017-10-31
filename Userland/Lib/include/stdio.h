#ifndef STDIO_H
#define STDIO_H

extern int int80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

#define BUFFER_SIZE 25*80+1000

void write(int fd, char* buffer, int size);

void read(int fd, char* buffer, int size);

void putChar(char c);

int getChar();

int printf(const char* format, ...);

int scanf(const char* format, ...);

int sscanf(const char* format, const char * str, ...);

int parseInt(char* string, int * value);

int readLine(char * buffer, int maxSize);

void exit(int value);

#endif
