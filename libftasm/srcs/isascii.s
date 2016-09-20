

global _ft_isascii

ret_false:
	mov rax, 0
	ret

_ft_isascii:
	cmp rdi, 0
	jl ret_false
	cmp rdi, 127
	jg ret_false
	mov rax, 1
	ret