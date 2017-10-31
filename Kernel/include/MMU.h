#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include <kernel.h>

uint64_t getPhysical();
int setUserland(uint64_t);
void changeAddress(char *);

#endif