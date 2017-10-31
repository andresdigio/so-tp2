#include <kernel.h>

void clearBSS(void * bssAddress, uint64_t bssSize){
	memset(bssAddress, 0, bssSize);
}

void * getStackBase(){
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}


void * initializeKernelBinary(){
	char buffer[10];
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress,
		dummyModule,
		shellModule
	};
	
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main(){	
	init_IDT();
	configurePICMask(0xF9);
	configurePICMaskS(0xEF);
	setUserland(0xC00000);
	updateCR3();
	sti();
	ncClear();
	memcpy(userland,shellModule,0x200000);
	((EntryPoint) userland)();
	return 0;
}