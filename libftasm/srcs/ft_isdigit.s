

global _ft_isdigit

ret_false:
	mov rax, 0
	ret

_ft_isdigit:
	cmp rdi, '0'
	jl ret_false
	cmp rdi, '9'
	jg ret_false
	mov rax, 1
	ret
