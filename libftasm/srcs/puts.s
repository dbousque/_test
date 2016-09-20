

%define MACH_SYSCALL(nb)	0x2000000 | nb
%define STDOUT				1
%define WRITE				4

global _ft_puts

make_call:
	syscall
	mov rsp, rbp
	pop rbp
	ret

get_len:
	cmp byte [r11], 0
	je make_call
	inc rdx
	inc r11
	jmp get_len

_ft_puts:
	push rbp
	mov rbp, rsp
	mov rax, MACH_SYSCALL(WRITE)
	mov rsi, rdi
	mov rdi, STDOUT
	mov r11, rsi
	mov rdx, 0
	jmp get_len