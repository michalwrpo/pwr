%include    './../functions.asm'

SECTION .data
msg     db      'Enter a number: ', 0h
end     db      'Digit sum: ', 0h

SECTION .bss
num:    resb    50

SECTION .text
global _start

_start:
    mov     eax, msg
    call    sprint

    mov     edx, 15
    mov     ecx, num
    mov     ebx, 0
    mov     eax, 3
    int     80h

    mov     eax, num
    call    atoi
    mov     ebx, 10
    mov     ecx, 0

.nextDigit:
    cmp     eax, 0
    jz      .sum

    xor     edx, edx
    div     ebx
    inc     ecx
    push    edx
    jmp     .nextDigit

.sum:
    cmp     ecx, 0
    jz      .finished
    pop     edx
    add     eax, edx
    dec     ecx
    jmp     .sum


.finished:
    push    eax
    mov     eax, end
    call    sprint
    pop     eax
    call    iprintLF
    call    quit

