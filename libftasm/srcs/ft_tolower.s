

global _ft_tolower

return_arg:
	mov rax, rdi
	ret

_ft_tolower:
	cmp rdi, 'A'
	jl return_arg
	cmp rdi, 'Z'
	jg return_arg
	sub rdi, 'A'
	add rdi, 'a'
	mov rax, rdi
	ret