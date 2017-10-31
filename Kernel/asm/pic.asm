GLOBAL configurePICMask
GLOBAL configurePICMaskS
GLOBAL checkISRM
GLOBAL checkISRS
GLOBAL eoi
GLOBAL irq0
GLOBAL irq1
GLOBAL irq7
GLOBAL irq12
GLOBAL irq15

extern irqDispatcher
%include "./asm/macros.m"

section .text

configurePICMask:
	
	mov rax, rdi
	out 21h, al
	ret

configurePICMaskS:
	mov rax, rdi
	out 0xa1, al
	ret

checkISRM:
	mov al, 0x0b
	out 0x20, al	;command to read isr next
	xor rax,rax
	in al,0x20

checkISRS:
	mov al, 0x0b
	out 0xA0, al	;command to read isr next
	xor rax, rax
	in al,0xA0

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

irq0: ; timer tick
	irqHandler 0

irq1: ; keyboard
	irqHandler 1

irq7:
	irqHandler 7

irq12: ; mouse
	irqHandlerS 12

irq15:
	irqHandlerS 15
