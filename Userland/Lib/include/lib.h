extern void sys_write(char*);
extern void sys_read(char*);
extern void sys_buffer(char*);
extern void sys_command(int,char*);
extern void sys_exit();
int strCmp(const char* s1, const char* s2);
int strLen(const char * s);
void putChar(char c);
char getChar();
char* itoa(int num, char* str, int base);
int getInt();