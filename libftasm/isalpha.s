

global _ft_isalpha

exit:
	ret

ret_true:
	mov rax, 1
	ret

ret_false:
	mov rax, 0
	ret

isupper:
	cmp rdi, 'A'
	jl ret_false
	cmp rdi, 'Z'
	jg ret_false
	jmp ret_true

islower:
	cmp rdi, 'a'
	jl ret_false
	cmp rdi, 'z'
	jg ret_false
	jmp ret_true

_ft_isalpha:
	call isupper
	cmp rax, 1
	je exit
	call islower
	cmp rax, 1
	je exit
	ret