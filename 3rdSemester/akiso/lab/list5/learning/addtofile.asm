%include    'functions.asm'

SECTION .data
filename    db      'file.txt', 0h
contents    db      'It works!', 0h 

SECTION .text
global _start

_start:
    mov     ecx, 1
    mov     ebx, filename
    mov     eax, 5          ; sys_open
    int     80h

    mov     edx, 2          ; SEEK_END
    mov     ecx, 0
    mov     ebx, eax
    mov     eax, 19         ; sys_lseek
    int     80h

    mov     edx, 9
    mov     ecx, contents
    mov     eax, 4
    int     80h

    call    quit