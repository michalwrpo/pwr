%include    './../functions.asm'

SECTION .data
ele     db      'Suma elementów: ', 0h
dia     db      'Suma przekątnej: ', 0h
err     db      'Zła ilość argumentów, program przyjmuje 9', 0h

SECTION .text
global _start

_start:
    pop     ecx
    pop     edx
    dec     ecx
    xor     edx, edx
    cmp     ecx, 9
    jne     .error
    xor     ebx, ebx

.nextNum:
    cmp     ecx, 0
    jz      .results
    dec     ecx
    pop     eax
    call    atoi
    add     ebx, eax
    cmp     ecx, 8
    je      .diagnal
    cmp     ecx, 4
    je      .diagnal
    cmp     ecx, 0
    je      .diagnal
    jmp     .nextNum

.diagnal:
    add     edx, eax
    jmp     .nextNum

.error:
    mov     eax, err
    call    sprintLF
    jmp     .finished

.results:
    mov     eax, ele
    call    sprint
    mov     eax, ebx
    call    iprintLF
    mov     eax, dia
    call    sprint
    mov     eax, edx
    call    iprintLF

.finished:
    call    quit