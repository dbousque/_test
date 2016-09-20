

%define MACH_SYSCALL(nb)	0x2000000 | nb
%define STDOUT				1
%define WRITE				4

global _ft_strdup
extern _malloc

ft_strlen:
	mov r11, rdi
	mov rax, 0
	mov rcx, -1
	cld
	repne scasb
	sub rdi, r11
	sub rdi, 1
	mov rax, rdi
	ret

ft_memcpy:
	mov rax, rdi
	mov rcx, rdx
	cld
	rep movsb
	ret

exit_error:
	pop rax
	pop rax
	mov rax, 0
	mov rsp, rbp
	pop rbp
	ret

_ft_strdup:
	push rbp
	mov rbp, rsp
	; saving arg
	push rdi
	call ft_strlen
	; putting len in rdi (arg to malloc)
	mov rdi, rax
	inc rdi
	; saving len
	push rdi
	call _malloc
	; has malloc failed ?
	cmp rax, 0
	je exit_error
	; getting len back and put as third argument
	pop rdx
	; getting arg back and put as second argument
	pop rsi
	mov rdi, rax
	call ft_memcpy
	mov rsp, rbp
	pop rbp
	ret