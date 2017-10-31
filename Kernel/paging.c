#include <stdint.h>
#include <kernel.h>

//PML4: 0x2000
//1stPDP: 0x3000
//userPD: 0x10000


uint64_t getPhysical(){
	uint64_t u = (uint64_t) userland;
	uint64_t * PDBase = (uint64_t*) 0x10000;
	uint64_t * userEntry = PDBase + ( u>>21 );
	return *userEntry & 0xFFFFFFFF00;
}


int setUserland(uint64_t port){
	uint64_t u = (uint64_t) userland;
	if(port < 0x400000 || port & 0x1FFFFF || port > 0xFF00000) //limite
		return 0;
	uint64_t * PDBase = (uint64_t*) 0x10000;
	uint64_t * userEntry = PDBase + (u>>21);  //a la base del primer PD le sumo el indice del userland para
	*userEntry = port | 0x8F;//+ 0x8F;								//tener el puntero a su entrada
	return 1;
}


void changeAddress(char * arg){
	uint64_t hex = toHex(arg);
	if(setUserland(hex)){
		updateCR3();
		ncPrint("physical address changed to: ");
		ncPrintHex(hex);
	}
	else{
		ncPrint("invalid address");
	}
}
