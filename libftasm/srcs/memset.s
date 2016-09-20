

global _ft_memset

_ft_memset:
	mov rcx, rdx
	mov al, sil
	cld
	rep stosb
	ret