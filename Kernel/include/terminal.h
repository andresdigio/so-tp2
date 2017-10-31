#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <kernel.h>
#include <MMU.h>

void backspaceBuffer();
void writeBuffer(uint8_t * c);
void clearBuffer();
void ls(char*);

char  const * commands[] = {"execute", "ls", "help", "clear"};
char * files[20] = {"dummy", "shell", 0};

uint8_t * const init_Buffer = (uint8_t*) 0x300000;
uint8_t * kBuffer = (uint8_t*) 0x300000;

#endif