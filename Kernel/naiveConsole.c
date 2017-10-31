#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

typedef uint8_t row[160];

static char buffer[64] = { '0' };
static const uint8_t * init_video= (uint8_t*) 0xB8000;
static row * video = 0xB8000;
static row videoBuffer[25] = {0};
static row selectionBuffer[25] = {0};
static uint8_t ci,cj;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

typedef struct{
	uint8_t x;
	uint8_t y; 
}Point;

static Point lastPosition =  {40,12};
static uint8_t lastChar = ' ', lastAttr = 0x0F;
static uint8_t selection;
static Point selection_i, selection_f;

void saveVideo(){
	video=init_video;
}

void printHelp(){
	ncPrint("ls - shows available files to execute");
	ncNewline();
	ncPrint("execute (file) - executes the file");
	ncNewline();
	ncPrint("clear - clears the terminal");
	ncNewline();
	ncPrint("help - shows the list of commands");
}


void ncPrint(const char * string){
	for (int i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void printAt(const char * string, int i, int j){
	uint8_t lastj = cj;
	uint8_t lasti = ci;
	cj = j;
	ci = i;
	ncPrint(string);
	cj=lastj;
	ci = lasti;
}

void scrollDown(){
	for(int k = 0; k < height-1; k++){
		for (int m = 0; m < width*2; m++){
			videoBuffer[k][m]=videoBuffer[k+1][m];
			video[k][m]=videoBuffer[k][m];
		}
	}
	
	for(int k=0; k<width; k++){
		video[height-1][2*k]=' ';
		video[height-1][2*k+1]=0x0F;
		videoBuffer[height-1][2*k]=' ';
		videoBuffer[height-1][2*k+1]=0x0F;
	}
	ci = height-1;
}

static void clearSelectionBuffer(){
	for(int k = 0; k < height-1; k++){
		for (int m = 0; m < width*2; m++){
			selectionBuffer[k][m] = 0;
		}
	}
}

static void copy(uint8_t iFrom,uint8_t jFrom,uint8_t iTo,uint8_t jTo){
	int l=iFrom,k=jFrom;
	while(!(l==iTo && k==jTo)){	
		selectionBuffer[l][2*k] = videoBuffer[l][2*k];
		k++;
		if(k % 80 == 0){
			l++;
			k=0;
		}
	}
}

void endSelection(){
	selection = 0;
	if(lastPosition.y > selection_i.y)
		copy(selection_i.y,selection_i.x,lastPosition.y,lastPosition.x);
	else if(lastPosition.y < selection_i.y)
		copy(lastPosition.y,lastPosition.x,selection_i.y,selection_i.x);	
	else if(selection_i.x < lastPosition.x)
		copy(selection_i.y,selection_i.x,lastPosition.y,lastPosition.x);
	else if(lastPosition.x < selection_i.x)
		copy(lastPosition.y,lastPosition.x,selection_i.y,selection_i.x);
}

void startSelection(){
	selection=1;
	selection_i.x=lastPosition.x;
	selection_i.y=lastPosition.y;
	clearSelectionBuffer();
}

void paste(){
	for(int k = 0; k < height-1; k++){
		for (int m = 0; m < width; m++){
			if(selectionBuffer[k][2*m])
				ncPrintChar(selectionBuffer[k][2*m]);
		}
	}
}

void ncPrintChar(char character){
	if(ci == height)
		scrollDown();
	if(!(ci==lastPosition.y && cj*2==lastPosition.x)){
		video[ci][cj] = character;
		video[ci][cj+1] = 0x0F;
	}else{
		lastChar=character;
		lastAttr=0x0F;
	}
	videoBuffer[ci][cj] = character;
	videoBuffer[ci][cj+1] = 0x0F;
	cj+=2;
	if(cj % 160 == 0){
		cj = 0;
		ci++;
	}
	saveVideo();
}

void ncNewline(){
	do{
		ncPrintChar(' ');
	}
	while(cj % 160 != 0);
}

void select(uint8_t iFrom, uint8_t jFrom, uint8_t iTo, uint8_t jTo){
	int l = iFrom, k = jFrom;
	while(!(l==iTo && k==jTo)){
		video[l][2*k+1] = 0x5F;
		k++;
		if(k % 80 == 0){
			l++;
			k=0;
		}
	}
}

void deselect(){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			video[i][2*j+1]=0x0F;
		}
	}
}

void printCursor(uint8_t x, uint8_t y){
	deselect();
	video[lastPosition.y][2*lastPosition.x] = lastChar;
	video[lastPosition.y][2*lastPosition.x+1] = lastAttr;
	videoBuffer[lastPosition.y][2*lastPosition.x] = lastChar;
	videoBuffer[lastPosition.y][2*lastPosition.x+1] = lastAttr;
	lastChar = videoBuffer[y][x*2];
	lastAttr = videoBuffer[y][2*x+1];
	video[y][x*2] =  30;
	if(selection){
		if(y > selection_i.y)
			select(selection_i.y,selection_i.x,y,x);
		else if(y < selection_i.y)
			select(y,x,selection_i.y,selection_i.x);	
		else if(x > selection_i.x)
			select(selection_i.y,selection_i.x,y,x);
		else if(x < selection_i.x)
			select(y,x,selection_i.y,selection_i.x);
	}
	lastPosition.x = x;
	lastPosition.y = y;
}

int outOfBounds(uint8_t a, char offset,int type){
	if(type == 0){
		//width
		if((char) a + offset < 0 || (char) a+offset >= 80)
			return 1;
	}
	else{
		//height
		if((char) a + offset < 0 || (char) a + offset >= 25)
			return 1;
	}
	return 0;
}

void printTime(){
	uint8_t lasti=ci,lastj=cj;
	ci=0;cj=0;	
	ncPrintHex(rtc(7));
	ncPrintChar('/');
	ncPrintHex(rtc(8));
	ncPrintChar('/');
	ncPrintHex(rtc(9));
	ncPrintChar(' ');
	ncPrintHex(rtc(4));
	ncPrintChar(':');
	ncPrintHex(rtc(2));
	ncPrintChar(':');
	ncPrintHex(rtc(0));
	ncPrintChar(' ');
	ci=lasti;cj=lastj;
}

void backspace(){
	if(ci != 0 && cj != 0 ){
		video[ci][cj-2] = ' ';
		videoBuffer[ci][cj-2] = ' ';
		cj-=2;
	}
}

void ncPrintDec(uint64_t value){
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value){
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value){
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base){
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear(){
	for (int i = 0; i < height; i++){
		for(int j=0; j < width*2;j+=2){
			video[i][j] = ' ';
			videoBuffer[i][j] = ' ';
			video[i][j+1] = 0x0F;
			videoBuffer[i][j+1] = 0x0F;
		}
	}
	ci = 0;
	cj = 0;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
