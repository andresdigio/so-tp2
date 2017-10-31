#include <interruptions.h>

//https://pastebin.com/f5fae4add

void irqDispatcher(int irq){
	handlers[irq]();
}

void addInterruption(uint64_t handler, int index){
	IDT[index].offset_l = (uint16_t) handler & 0xFFFF;
	IDT[index].offset_m = (uint16_t) (handler >> 16) & 0xFFFF;
	IDT[index].offset_h = (uint32_t) (handler >> 32) & 0xFFFFFFFF;
	
	IDT[index].selector = 0x08;
	IDT[index].zero_l = 0;
	
	IDT[index].attrs = 0x8E;
	IDT[index].zero_h = 0;	
}

void init_IDT(){
	init_Mouse();
	addInterruption((uint64_t) pageFaultHandler, 0x0E);
	addInterruption((uint64_t) irq0, 0x20);
	addInterruption((uint64_t) irq1, 0x21);
	addInterruption((uint64_t) irq7, 0x27);
	addInterruption((uint64_t) irq12, 0x2C);
	addInterruption((uint64_t) irq15, 0x2F);
	addInterruption((uint64_t) sys_callsHandler, 0x80);
}

void timerTickC(){}

void nothing(){}

void keyboardC(){
	if(inb(0x64)&0x20)
		return;
	
	static char shiftPressed = FALSE;
	uint8_t index = inb(0x60);

	if(index == 0x2A || index == 0x36)
		shiftPressed = TRUE;
	else if(index == 0xAA || index == 0xB6)
		shiftPressed = FALSE;

	char * s = shiftPressed ? SHIFT_KEYS_VALUES[index] : KEYS_VALUES[index];

	if(index == 0x0E){
		backspaceBuffer();
	}
	else if(index < 0x81 && index != 0x2A && index != 0x36 && index != 0x1C && index != 0xE0 && index != 0x38){
		writeBuffer(s);
	}
	else if(index == 0x1C){
		writeBuffer("\n");
	}
}
