#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <asm.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;


static const uint64_t PageSize = 0x200000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const dummyModule = (void*) 0x800000;
static void * const shellModule = (void*) 0x600000;
static void * userland = (void*) 0xC00000;


int setUserland(uint64_t port);
void init_IDT();
void printTime();
void init_terminal();
void configurePICMask(uint64_t address);
void configurePICMaskS(uint64_t address);
void sti();
uint64_t toHex(char*);

typedef struct{
	uint8_t name[32];
	uint64_t base;
	uint32_t size;
}fileEntry_t;

//static fileEntry_t * const fileTable = 0x600000;

typedef int (*EntryPoint)();

#endif