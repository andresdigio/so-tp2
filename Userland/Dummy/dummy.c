#include "lib.h"
int main(){
	char *s = "running dummy";
	sys_write(s);
	putChar('\n');
	sys_exit();
}