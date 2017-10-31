GLOBAL configurePICMaskMaster
GLOBAL configurePICMaskSlave

section .text

configurePICMaskMaster:
	
	mov rax, rdi
	out 0x21, al
	ret

configurePICMaskSlave:
	
	mov rax, rdi
	out 0xA1, al
	ret