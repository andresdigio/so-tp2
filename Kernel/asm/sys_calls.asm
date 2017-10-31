GLOBAL sys_callsHandler
GLOBAL load
GLOBAL pageFaultHandler
extern getStackBase
extern memcpy
extern exitC
extern writeC
extern readC
extern bufferC
extern commandC
extern ncPrint

section .rodata
	errorMessage equ "Flasheaste hermano"


section .text

pageFaultHandler:
	mov rdi, errorMessage
	call ncPrint
	call exitC
	ret

load:
	mov rdx,0x200000
	call memcpy
	call getStackBase
	mov rsp, rax
	jmp rdi

sys_callsHandler:
	
	cmp bl, 0x0
	je .exit
	
	cmp bl, 0x1
	je .write

	cmp bl, 0x2
	je .read

	cmp bl, 0x3
	je .buffer

	cmp bl, 0x4
	je .command

.write:
	mov rdi, rax
	call writeC
	jmp .finished

.read:
	call readC
	jmp .finished

.buffer:
	mov rdi, rax
	call bufferC
	jmp .finished

.command:
	mov rdi, rax
	mov QWORD [rsp],commandC
	jmp .finished

.exit:
	mov QWORD [rsp],exitC
	jmp .finished

.finished:
	iretq

