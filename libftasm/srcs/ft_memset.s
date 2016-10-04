

global _ft_memset

_ft_memset:
	; save argument, to put it in rax at the end
	push rdi
	mov rcx, rdx
	mov al, sil
	cld
	rep stosb
	pop rax
	ret
