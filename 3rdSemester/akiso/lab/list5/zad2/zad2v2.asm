%include    './../functions.asm'

SECTION .data
ele     db      'Suma elementów: ', 0h
dia     db      'Suma przekątnej: ', 0h
a1_1     dd      18
a1_2     dd      27
a1_3     dd      36
a2_1     dd      45
a2_2     dd      54
a2_3     dd      63
a3_1     dd      72
a3_2     dd      81
a3_3     dd      90

SECTION .text
global _start

_start:
    mov     eax, 0
    xor     ebx, ebx
    xor     edx, edx

    mov     eax, [a1_1]
    add     ebx, eax
    add     edx, eax

    mov     eax, [a1_2]
    add     ebx, eax

    mov     eax, [a1_3]
    add     ebx, eax

    mov     eax, [a2_1]
    add     ebx, eax

    mov     eax, [a2_2]
    add     ebx, eax
    add     edx, eax

    mov     eax, [a2_3]
    add     ebx, eax

    mov     eax, [a3_1]
    add     ebx, eax

    mov     eax, [a3_2]
    add     ebx, eax

    mov     eax, [a3_3]
    add     ebx, eax
    add     edx, eax

    mov     eax, ele
    call    sprint
    mov     eax, ebx
    call    iprintLF

    mov     eax, dia
    call    sprint
    mov     eax, edx
    call    iprintLF

    call    quit