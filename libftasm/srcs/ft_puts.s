

%define MACH_SYSCALL(nb)	0x2000000 | nb
%define STDOUT				1
%define WRITE				4

section .data
data:
	.null db "(null)", 0
	.newline db 10

section .text
	global _ft_puts

exit_error:
	mov rax, -1
	jmp exit

exit:
	mov rsp, rbp
	pop rbp
	ret

print_newline:
	mov rax, MACH_SYSCALL(WRITE)
	mov rdi, STDOUT
	lea rsi, [rel data.newline]
	mov rdx, 1
	syscall
	jc exit_error
	jmp exit

make_call:
	syscall
	jc exit_error
	jmp print_newline

get_len:
	cmp byte [r11], 0
	je make_call
	inc rdx
	inc r11
	jmp get_len

print_null:
	lea rdi, [rel data.null]
	jmp _ft_puts

_ft_puts:
	cmp rdi, 0
	je print_null
	push rbp
	mov rbp, rsp
	mov rax, MACH_SYSCALL(WRITE)
	mov rsi, rdi
	mov rdi, STDOUT
	mov r11, rsi
	mov rdx, 0
	jmp get_len