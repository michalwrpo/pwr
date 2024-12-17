
; nasm -fbin boot.asm
; qemu-system-i386 -drive format=raw,file=boot

bits 16
org 0x7c00                  ; load boot sector to RAM memory

boot:
    mov     ax, 0x2401
    int     15h             ; enable A20 gate
    mov     ax, 0x13        ; wlaczenie trybu graficznego 320x200
    int     10h             ; BIOS interrupt 
    cli                     ; clear interrupt flags, disable external interrupts 
    lgdt    [gdt_pointer]   ; ustawienie tablicy GDT (Global Descriptor Table)
    mov     eax, cr0        ; wlaczenie trybu chronionego
    or      eax, 0x1
    mov     cr0, eax
    jmp     CODE_SEG:boot2  ; reload segment registers
gdt_start:                  ; tablica GDT
    dq 0x0                  ; GDT starts with null 8-bytes
gdt_code:                   ; kernel mode code
    dw 0xFFFF               ; first 16 bits of limit
    dw 0x0                  ; 24 bits of base 
    db 0x0                  ; continued
    db 10011010b            ; Access byte
    db 11001111b            ; 4 bits of limit (F) and 4 bits of flags (C)
    db 0x0                  ; last 8 bits of base
gdt_data:                   ; kernel mode data
    dw 0xFFFF               ; almost the same as above
    dw 0x0                  
    db 0x0              
    db 10010010b            ; only differnce, access byte is 0x92 instead of 0x9A
    db 11001111b
    db 0x0
gdt_end:
gdt_pointer:
    dw gdt_end - gdt_start  ; lengths of gdt
    dd gdt_start            ; address to the start of gdt

CODE_SEG equ gdt_code - gdt_start   ; offset of kernel mode code
DATA_SEG equ gdt_data - gdt_start   ; offset of kernel mode data

bits 32
boot2:
    mov     ax, DATA_SEG    ; reload segment registers
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    mov     edi, 50
.mandel:
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
    mov     eax, 3
    mul     edi
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
    mov     eax, 5
    mul     edi
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

.black:
    mov     al, 0
    jmp     .color

.end:
    finit                   ; clean the stack

    mov     eax, esi
    add     eax, 128
    ; push    edx
    ; push    ecx
    ; mov     ecx, 8
    ; xor     edx, edx
    ; div     ecx
    ; pop     ecx
    ; pop     edx
    ; cmp     al, 31
    ; je      .black

.color:
    mov     byte [ebx], al       ; set color
    add     ebx, 1
    inc     dx
    cmp     dx, 320
    jne     .loop1               
    dec     cx
    jne     .loop2
    mov     esi, 0
    add     edi, 50
    mov     eax, 0

.busyLoop:
    inc     eax
    cmp     eax, 1000000000
    jne     .busyLoop

    jmp     .mandel    
halt:
    cli
    hlt                      ; halt

times 510 - ($-$$) db 0      ; fill rest of first sector with 0
dw 0xaa55

