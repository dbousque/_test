

%define MACH_SYSCALL(nb)	0x2000000 | nb
%define STDOUT				1
%define WRITE				4
%define READ				3
%define BUFSIZE				256

section .text
	global _ft_cat
	extern _read

exit:
	; remove our fd arg
	pop rax
	; remove our buffer
	add rsp, BUFSIZE
	mov rsp, rbp
	pop rbp
	ret

make_call:
	syscall
	jc exit
	jmp read_data

print_string:
	; test if read ret == -1
	cmp rax, -1
	je exit
	; test if read ret == 0
	cmp rax, 0
	je exit

	mov rdx, rax
	mov rax, MACH_SYSCALL(WRITE)
	mov rdi, STDOUT
	; put buf address on rsi (rsp + 8, size of a reg)
	mov rsi, rsp
	add rsi, 8
	jmp make_call

read_data:
	; load fd as first arg
	pop rdi
	; then is the buf on stack, load it as second arg
	mov rsi, rsp
	; save fd again
	push rdi
	mov rax, MACH_SYSCALL(READ)
	; len of our buffer
	mov rdx, BUFSIZE
	syscall
	jc exit
	jmp print_string

_ft_cat:
	push rbp
	mov rbp, rsp

	; reserve bufsize bytes on stack
	sub rsp, BUFSIZE
	; save arg
	push rdi
	jmp read_data