#include "naiveConsole.h"

uint8_t mouse_cycle = 0, leftPressed = 0, selectionMade = 0, selection = 0;
char mouse_byte[3];
float mouse_x=40;
float mouse_y=12;

void mouse_wait(unsigned char type){
  unsigned int _time_out=100000;
  if(type==0){
    while(_time_out--) { //Data
      if((inb(0x64) & 1)==1)
        return;
    }
    return;
  }
  else{
    while(_time_out--){ //Signal
      if((inb(0x64) & 2)==0)
        return;
    }
    return;
  }
}

void mouse_write(unsigned char a_write){
//Wait to be able to send a command
  mouse_wait(1);
//Tell the mouse we are sending a command
  outb(0x64,0xD4);
//Wait for the final part
  mouse_wait(1);
//Finally write
  outb(0x60,a_write);
}

uint8_t mouse_read(){
//Get response from mouse
  mouse_wait(0);
  return inb(0x60);
}

void mouseC(){
  if(!(inb(0x64) & 0x20))
    return;
  mouse_byte[mouse_cycle++] = mouse_read();
  if(mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40)
    mouse_cycle = 0;
  if(mouse_cycle == 3){
    mouse_cycle = 0;
    if(mouse_byte[0] & 0x1){
      if(!leftPressed)
        leftPressed = 1;
      else{
        if(!selection){
          selection=1;
          startSelection();
        }
      }
    }
    else if(mouse_byte[0] & 0x2){
      if(selectionMade){
          paste();
      }
    }
    else{
      leftPressed = 0;
      if(selection){
        endSelection();
        selectionMade = 1;
        selection = 0;
      }
    }
    if(!outOfBounds((int)mouse_x,mouse_byte[1],0))
      mouse_x+=mouse_byte[1];
    if(!outOfBounds((int)mouse_y,-mouse_byte[2],1))
      mouse_y-=mouse_byte[2];
    printCursor((int) mouse_x,(int) mouse_y);
  }
}

void init_Mouse(){
	//enable auxiliary mouse device
	mouse_wait(1);
	outb(0x64,0xA8);
	//enable interrupts
	mouse_wait(1);
	outb(0x64,0x20);
	mouse_wait(0);
	uint8_t status = (inb(0x60)|2);
	mouse_wait(1);
	outb(0x64,0x60);
	mouse_wait(1);
	outb(0x60,status);
	mouse_write(0xF6);
	mouse_read();
	mouse_write(0xF4);
	mouse_read();
}
