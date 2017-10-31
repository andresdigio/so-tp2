#include <stdint.h>

int readCommand();

char  const * commands[] = {"execute", "ls", "help", "clear", "set"};
char kBuffer[400] = {0};

int main(){
	clearBuffer();
	char c = 0;
	sys_write(">> ");
	do{
		c = getChar();
	}while(c != '\n');
	sys_buffer(kBuffer);
	if(readCommand() != 3) //si no es clear
		putChar('\n');
	sys_exit();
}

void clearBuffer(){
	for(int i = 0; kBuffer[i] != 0; i++)
		kBuffer[i++] = 0;
}

int possibleCommand(char c){
	switch(c){
		case 'e':
				return 0;
		case 'l':
				return 1;
		case 'h':
				return 2;
		case 'c':
				return 3;
		case 's':
				return 4;
		default:
				return -1;
	}
}

int checkCommand(int index){
	if(index==-1)
		return 1;
	uint8_t str[15];
	int len = strLen((char *) commands[index]);
	int i;
	for(i=0; i< len; i++)
		str[i] = kBuffer[i];
	str[i-1] = 0;
	return strCmp((char *) commands[index],(char *) str);
}

int readCommand(){
	int index = possibleCommand(kBuffer[0]);
	if(checkCommand(index) == 0){
		if(index==4)
			sys_command(index, kBuffer + 4);
		else
			sys_command(index,kBuffer + 8);
		return index;
	}
	else{
		sys_write("Unkown Command");
	}
	clearBuffer();
	return -1;
}