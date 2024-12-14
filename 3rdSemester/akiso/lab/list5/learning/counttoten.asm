%include 'functions.asm'

SECTION .text
global _start

_start:
    mov ecx,    0

nextNum:
    inc ecx

    mov eax,    ecx
    call    iprintLF 
    cmp ecx,    10
    jne nextNum

    call    quit