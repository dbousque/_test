

global _ft_memcpy

_ft_memcpy:
	mov rax, rdi
	mov rcx, rdx
	cld
	rep movsb
	ret