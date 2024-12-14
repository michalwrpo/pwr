%include    'functions.asm'

SECTION .data
filename    db      'file.txt', 0h

SECTION .text
global _start

_start:
    mov     ebx, filename
    mov     eax, 10         ; sys_unlink (delete)
    int     80h

    call    quit