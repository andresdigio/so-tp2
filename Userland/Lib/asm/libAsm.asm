GLOBAL sys_exit
GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_buffer
GLOBAL sys_command

section .text

sys_exit:
	mov rbx, 0x0
	int 80h
	ret

sys_write:
	push rbx
	mov rax,rdi
	mov rbx, 0x1
	int 80h
	pop rbx
	ret

sys_read:
	push rbx
	mov rbx, 0x2
	int 80h
	pop rbx
	ret

sys_buffer:
	push rbx
	mov rax, rdi
	mov rbx, 0x3
	int 80h
	pop rbx
	ret

sys_command:
	push rbx
	push rcx
	mov rax, rdi
	mov rcx, rsi
	mov rbx, 0x4
	int 80h
	pop rcx
	pop rbx
	ret