%include    'functions.asm'

SECTION .data
msg1    db  'Fizz', 0h
msg2    db  'Buzz', 0h

SECTION .text
global _start

_start:
    mov     ecx, 0
    mov     edx, 0
    mov     esi, 0

loop:
    inc     ecx
    mov     esi, 0

.fizz:
    mov     eax, ecx
    mov     ebx, 3
    xor     edx, edx
    div     ebx
    cmp     edx, 0
    jnz     .buzz
    inc     esi
    mov     eax, msg1
    call    sprint

.buzz:
    mov     eax, ecx
    mov     ebx, 5
    xor     edx, edx
    div     ebx
    cmp     edx, 0
    jnz     .neither
    inc     esi
    mov     eax, msg2
    call    sprint

.neither:
    cmp     esi, 0
    jnz     .continue
    mov     eax, ecx
    call    iprint

.continue:
    mov     eax, 0Ah
    push    eax
    mov     eax, esp
    call    sprint
    pop     eax
    cmp     ecx, 100
    jne     loop

    call    quit