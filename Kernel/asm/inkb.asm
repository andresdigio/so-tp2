%include "./asm/macros.m"

GLOBAL inkb

section .text

inkb:
	xor rax,rax
	in al, 0x60
	ret
