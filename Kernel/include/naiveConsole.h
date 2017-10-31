#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

void ncPrint(const char * string);
void ncPrintChar(char character);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();
void printAt(const char * string, int i, int j);
void printCursor(uint8_t x, uint8_t y);
void backspace();
int outOfBounds(uint8_t a, char offset,int type);
void paste();
void printHelp();
void endSelection();
void startSelection();

#endif