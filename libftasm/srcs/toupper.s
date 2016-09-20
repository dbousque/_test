

global _ft_toupper

return_arg:
	mov rax, rdi
	ret

_ft_toupper:
	cmp rdi, 'a'
	jl return_arg
	cmp rdi, 'z'
	jg return_arg
	sub rdi, 'a'
	add rdi, 'A'
	mov rax, rdi
	ret