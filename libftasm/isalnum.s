

global _ft_isalnum

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

_ft_isdigit:
	cmp rdi, '0'
	jl ret_false
	cmp rdi, '9'
	jg ret_false
	mov rax, 1
	ret

_ft_isalnum:
	call _ft_isalpha
	cmp rax, 1
	je exit
	call _ft_isdigit
	cmp rax, 1
	je exit
	ret