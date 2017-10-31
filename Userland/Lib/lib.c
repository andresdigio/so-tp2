#include <lib.h>
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

void putChar(char c){
	sys_write(&c);
}
/*
void echo(){
	sys_command(5);
}
*/
char getChar(){
	char aux;
	sys_read(&aux);
	return aux;
}