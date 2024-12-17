%include    './../functions.asm'

SECTION .text
global _start

_start:
    mov     eax, 3735928559
    mov     ebx, 16
    mov     ecx, 0

.loop:
    xor     edx, edx
    div     ebx
    add     edx, 48
    cmp     edx, 57
    jg      .handleLetters

.toStack:
    inc     ecx
    push    edx
    cmp     eax, 0
    jz      .print
    jmp     .loop

.handleLetters:
    add     edx, 7
    jmp     .toStack

.print:
    dec     ecx
    mov     eax, esp
    call    sprint
    pop     eax

    cmp     ecx, 0
    jnz     .print

    mov     edx, 1
    mov     ecx, 0Ah
    push    ecx
    mov     ecx, esp
    mov     ebx, 1
    mov     eax, 4
    int     80h

.finished:
    call    quit
    