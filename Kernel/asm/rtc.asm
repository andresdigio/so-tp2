GLOBAL rtc 
section .text

rtc:
	mov rax, rdi
	and rax, 0xFF
	out 70h, al
	in al, 71h
	ret
