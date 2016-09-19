

%define MACH_SYSCALL(nb)	0x200000000 | nb
%define STDOUT				1
%define WRITE				4

global _ft_puts
global _get_len

make_call:
	syscall
	ret

get_len:
	cmp byte [r8], 0
	je make_call
	inc rdx
	inc r8
	jmp get_len

_ft_puts:
	mov rax, MACH_SYSCALL(WRITE)
	mov rsi, rdi
	mov rdi, STDOUT
	mov r8, rsi
	mov rdx, 0
	jmp get_len


ret_get_len:
	ret

actual_get_len:
	cmp byte [rdi], 0
	je ret_get_len
	inc rax
	inc rdi
	jmp actual_get_len

_get_len:
	mov rax, 0
	jmp actual_get_len