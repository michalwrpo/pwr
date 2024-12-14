%include    'functions.asm'

SECTION .data
filename    db  'file.txt', 0h
contents    db  'Hello, World!', 0h

SECTION .bss
fileContents    resb    255,

SECTION .text
global _start

_start:
    mov     ecx, 0777o
    mov     ebx, filename
    mov     eax, 8
    int     80h

    mov     edx, 13
    mov     ecx, contents
    mov     ebx, eax
    mov     eax, 4
    int     80h

    mov     ecx, 0
    mov     ebx, filename
    mov     eax, 5
    int     80h

    mov     edx, 13
    mov     ecx, fileContents
    mov     ebx, eax
    mov     eax, 3
    int     80h

    mov     eax, fileContents
    call    sprintLF
    
    mov     ebx, ebx
    mov     eax, 6
    int     80h

    call    quit
 