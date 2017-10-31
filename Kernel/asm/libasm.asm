GLOBAL cpuVendor
GLOBAL inb
GLOBAL outb
GLOBAL updateCR3
GLOBAL sti
GLOBAL cli
GLOBAL eoi
GLOBAL rtc

section .text

sti:
	sti
	ret

cli:
	cli
	ret

updateCR3:
	mov rax, cr3
	mov cr3, rax
	ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

inb:
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	xor rax, rax

	in al, dx

	mov rsp, rbp
	pop rbp
	ret

outb:
	push rbp
	mov rbp, rsp

	mov rax, rsi
	mov rdx, rdi
	out dx, al

	mov rsp,rbp
	pop rbp
	ret

eoi:
	push rbp
	mov rbp,rsp

	mov al,0x20 ;EOI
	cmp rdi,0
	je .PIC0
	cmp rdi,1
	je .PIC1
	jmp .end

.PIC0:
	out 0x20,al
	jmp .end

.PIC1:
	out 0xA0,al

.end:
	mov rsp, rbp
	pop rbp

rtc:
	mov rax, rdi
	and rax, 0xFF
	out 70h, al
	in al, 71h
	ret
