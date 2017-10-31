GLOBAL sti
GLOBAL cli

section .text

sti:
	sti
	ret

cli:
	cli
	ret