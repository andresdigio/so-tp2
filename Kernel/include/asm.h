#ifndef ASM_H
#define ASM_H

uint8_t inb(uint64_t);
void outb(uint64_t,uint64_t);
void updateCR3();
void sti();
void cli();

#endif