%include    './../functions.asm'

SECTION .data
msg     db      ' ', 0h
msg2    db      '|', 0h

SECTION .text
global _start

_start:
.mandel:
    mov     edi, 50
    mov     ebx, 0xa0000     ; adres ekranu graficznego
    mov     cx, 200          ; 200 lini ekranu
.loop2:
    mov     dx, 0            ; 320 piksli na linie
.loop1:
    mov     esi, 0
    mov     eax, 255          ; insert limit into float stack
    push    eax
    fild    dword [esp]
    pop     eax
                            ; z0 = a + bi 
    push    cx
    fild    word [esp]
    pop     ax
    mov     eax, 150
    push    eax
    fisub   dword [esp]
    pop     eax
    mov     eax, edi
    push    eax
    fidiv   dword [esp]
    pop     eax             ; store b

    push    dx
    fild    word [esp]
    pop     ax
    mov     eax, 240
    push    eax
    fisub   dword [esp]
    pop     eax
    mov     eax, edi
    push    eax
    fidiv   dword [esp]
    pop     eax             ; store a

    fld     st1             ; our stack currently has
    fld     st1             ; x, y, a, b, lim, where x=a, y=b

.mandelbrotLoop:
    inc     esi
                            ; z = x + iy
    fld     st1             ; store y

    mov     eax, 2          ; store 2
    push    eax
    fild   dword [esp]
    pop     eax

    fmulp   st3
    fld     st1
    fmulp   st3             ; st2 = 2xy

    fld     st4             ; load b
    faddp   st3             ; st2 = 2xy + b

    fld     st1
    fmulp   st2, st0        ; change st1 to x^2

    fld     st0
    fmulp   st1, st0        ; change st0 to y^2

    fsubp   st1             ; st0 = x^2 - y^2
    fadd    st2             ; st0 = x^2 - y^2 + a
                            ; st0 + i*st1 = z^2 + c
    fld     st1
    fmul    st0, st0

    fld     st1
    fmul    st0, st0

    faddp   st1             ; square of abs(z^2 + c)

    fcomi   st5
    jnb     .greater

    mov     eax, 0
    push    eax
    fistp   dword [esp]     ; remove distance from stack
    pop     eax

    cmp     esi, 127
    je      .end

    jmp     .mandelbrotLoop

.greater:
    mov     eax, 0
    push    eax
    fistp   dword [esp]     ; remove distance from stack
    pop     eax
    jmp     .end

.end:
    finit                   ; clean the stack
    mov     ax, dx
    call    iprint
    mov     eax, msg
    call    sprint
    mov     ax, cx
    call    iprint
    mov     eax, msg
    call    sprint
    mov     eax, esi
    call    iprint
    mov     eax, msg2
    call    sprint


    inc     dx
    cmp     dx, 320
    jne     .loop1               
    dec     cx
    jne     .loop2
    mov     esi, 0
    add     edi, 50
    jmp     .mandel    

    call    quit