

global _ft_strcat

exit_goend:
	ret

goto_end_of_rdi:
	cmp byte [rdi], 0
	je exit_goend
	inc rdi
	jmp goto_end_of_rdi

exit_fill:
	mov byte [rdi], 1
	ret

subset:
	cmp byte [rdi], 0
	je exit_fill

_ft_strcat:
	call goto_end_of_rdi
	call subset
	ret