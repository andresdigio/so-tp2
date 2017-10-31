#ifndef SYS_H
#define SYS_H

#include <stdint.h>
#include <naiveConsole.h>
#include <kernel.h>
#include <terminal.h>
#include <asm.h>

void copyBuffer(char *c);
void clearBuffer();
void load(void *,void*);

#endif