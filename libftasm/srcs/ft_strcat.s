

global _ft_strcat

goto_end_of_rdi:
	cmp byte [rdi], 0
	je fill_at_end
	inc rdi
	jmp goto_end_of_rdi

exit_fill:
	mov byte [rdi], 0
	pop r8
	ret

fill_at_end:
	cmp byte [rsi], 0
	je exit_fill
	mov r8b, [rsi]
	mov byte [rdi], r8b
	inc rdi
	inc rsi
	jmp fill_at_end

_ft_strcat:
	push r8
	mov rax, rdi
	jmp goto_end_of_rdi
