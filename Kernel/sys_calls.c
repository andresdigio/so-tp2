#include <stdint.h>
#include <naiveConsole.h>
#include <kernel.h>
#include <sys_calls.h>
#include <terminal.h>
#include <asm.h>

void ls();
void readFile(char*);
uint64_t toHex(char*);
void updateCR3();

(void *) functions(char *)[] = {readFile,ls,printHelp,ncClear,changeAddress};

void exitC(){
	clearBuffer();
	load(userland,shellModule);
}	

void writeC(char *c){
	if(*c == '\n')
		ncNewline();
	else
		ncPrint(c);
}

void readC(char *c){
	*c = consumeC();
}

void bufferC(char *c){
	copyBuffer(c);
	ncNewline();
}

void commandC(int type, char * arg){
	functions[type](arg);
	switch(type){
		case 0:
			readFile(arg);
			break;
		case 1:
			ls();
			break;
		case 2:
			printHelp();
			break;
		case 3:
			ncClear();
			break;
		case 4:


		}
	}	
	clearBuffer();
	if(type != 3)
		ncNewline();
	load(userland,shellModule);
}
