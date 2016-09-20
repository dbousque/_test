

global _ft_strlen
global _ft_my_strlen

_ft_strlen:
	mov r11, rdi
	mov rax, 0
	mov rcx, -1
	cld
	repne scasb
	sub rdi, r11
	sub rdi, 1
	mov rax, rdi
	ret