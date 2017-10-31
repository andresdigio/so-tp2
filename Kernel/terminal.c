#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <terminal.h>
#include <kernel.h>

char  const * commands[] = {"execute", "ls", "help", "clear"};
char * files[20] = {"dummy", "shell", 0};

uint8_t * const init_Buffer = (uint8_t*) 0x300000;
uint8_t * kBuffer = (uint8_t*) 0x300000;

uint64_t getPhysical();

int strCmp(const char* s1, const char* s2){
    while(*s1 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int strLen(const char * s){
	char * str = s;
	while(*(str++));
		return str - s;
}


char consumeC(){
	if(kBuffer == init_Buffer)
		return 0;
	return *(kBuffer-1);
}

void ls(char * arg){
	for(int i = 0; files[i] != 0; i++){
		ncPrint(files[i]);
		ncPrintChar(' ');
	}	
}

int possibleFile(char c){
	switch(c){
		case 'd':
				return 0;
		case 's':
				return 1;
		default:
				return -1;
	}
}

void execute(int index){
	switch(index){
		case 0:
			load(userland, dummyModule);
			clearBuffer();
			kBuffer = init_Buffer;
			break;
		case 1:
			load(userland, shellModule);
			break;
	}
}

int checkFile(int index, char * name){
	if(index==-1)
		return 1;
	return strCmp((char *) files[index],name);
}

void readFile(char * name){
	int index = possibleFile(*name);
	if(checkFile(index, name) == 0){
		ncPrint("Running module from: ");
		ncPrintHex(getPhysical());
		ncNewline();
		execute(index); 
	}
	else{
		ncPrint("File not found");
	}
}

void backspaceBuffer(){
	if(kBuffer == init_Buffer)
		return;
	backspace();
	*(--kBuffer) = 0;
}

void clearBuffer(){
	while(kBuffer > init_Buffer)
		*(--kBuffer) = 0;
	kBuffer=init_Buffer;
}

void copyBuffer(char *c){
	if(kBuffer==init_Buffer)
		return;
	char *i = init_Buffer;
	while(i != kBuffer-1)
		*c++ = *i++;
	*c = 0;
	clearBuffer();
}

void writeBuffer(uint8_t * c){
	*(kBuffer++) = *c;
	if(*c != '\n')
		ncPrint(c);
	*kBuffer = 0;
}
