

global _ft_bzero

exit:
	ret

_ft_bzero:
	cmp rsi, 0
	je exit
	mov byte [rdi], 0
	inc rdi
	sub rsi, 1
	jmp _ft_bzero