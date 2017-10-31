#ifndef INTERRUPTIONS_H
#define INTERRRUPTIONS_H

#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <scanCode.h>
#include <terminal.h>

typedef struct {
   uint16_t offset_l; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero_l;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t attrs; // type and attributes
   uint16_t offset_m; // offset bits 16..31
   uint32_t offset_h; // offset bits 32..63
   uint32_t zero_h;     // reserved
}IDTDesc ;

#define TRUE 1
#define FALSE 0

void init_Mouse();
void mouseC();

typedef void (*handler_t)(void);

uint8_t inb(uint8_t * port);
void outb(uint8_t * port, uint8_t byte);
void eoi(uint8_t type);
uint8_t checkISRM();
uint8_t checkISRS();
void pageFaultHandler();
void irq0();
void irq1();
void irq7();
void irq12();
void irq15();
void sys_callsHandler();

#endif

void timerTickC();
void keyboardC();
void mouseC();
void nothing();

static IDTDesc* IDT = (IDTDesc*) 0x0;
static handler_t handlers[] = {timerTickC, keyboardC, nothing, nothing, nothing, nothing, nothing, nothing, nothing, nothing, nothing, nothing, mouseC,nothing,nothing,nothing};