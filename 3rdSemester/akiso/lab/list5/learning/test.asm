%include    'functions.asm'

SECTION .data
msg     db      '!!!', 0h

SECTION .text
global _start

_start:
    mov     eax, 10
    jmp     .loop

.flagset:
    mov     eax, msg
    call    sprintLF
    jmp     .end

.loop:
    call    iprintLF
    dec     eax
    jz      .flagset
    jmp     .loop

.end:
    call    quit