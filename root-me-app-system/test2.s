global  _main
extern  _printf
extern  _ReadFile@20
extern  _WriteFile@20
extern  _GetStdHandle@4
extern  _CreateFileA@28
    extern  _ExitProcess@4

section .data
    fmt:        db '%d', 0Dh, 0Ah, 0    ; newline and NULL terminated
    access:     dd 0x10000000
    filename:   db 'ThisIsATestFile.txt', 0

    buflen:     dd 2048     ; Size of our buffer to be used for read
    dwBytesRead:dw 0

section .bss
    buffer:     resb 2048   ; A 2 KB byte buffer used for read

section .text
_main:
; CreateFile@28 - OpenFile
xor rax, rax
push rax            ; 7 param - Handle
push 128            ; 6 param - FILE_ATTRIBUTE_NORMAL
push 4              ; 5 param - OPEN_ALWAYS
push rax            ; 4 param - Default security
push rax            ; 3 param - Do not share
push DWORD [access] ; 2 param - Generic All
push filename       ; 1 param - FileName
call _CreateFileA@28

    mov ebx, eax    ; copy the handle into ebx

; ReadFile@20
xor rax, rax
push rax
push dwBytesRead
push DWORD [buflen]
push buffer
push rbx    ; handle
call _ReadFile@20

mov rsi, rax    ; get the amount of bytes read

; GetHandle - Output
push -11
call _GetStdHandle@4
mov rbx, rax    ; copy the handle into ebx

; WriteFile@20
xor rax, rax
push rax
push rax
push rsi
push buffer
push rbx
call _WriteFile@20



; ExitProcess(0)
    push    0
    call    _ExitProcess@4
