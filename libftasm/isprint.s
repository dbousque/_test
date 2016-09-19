

global _ft_isprint

ret_false:
	mov rax, 0
	ret

_ft_isprint:
	cmp rdi, ' '
	jl ret_false
	cmp rdi, '~'
	jg ret_false
	mov rax, 1
	ret