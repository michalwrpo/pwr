%include    './../functions.asm'

SECTION .data
space   db      ' ', 0h

SECTION .bss
numArr  resd      100000        ; array of 100,000 ints

SECTION .text
global main

main:
    mov     ecx, 0              ; ecx plays role of index looping through array
    mov     ebx, 1              ; ebx is used to go through all numbers smaller than 100,000

.init:
    mov     [numArr + ecx], ebx ; insertion of numbers into array
    inc     ebx
    add     ecx, 4              ; each int is 4 bytes big
    cmp     ecx, 400000         ; size of array: 100,000 * 4 = 400,000 
    jne     .init

    mov     ebx, 0
    mov     [numArr], ebx       ; 1 is not a prime
    mov     ecx, 0
    mov     edx, 0              ; edx will be used to insert 0s

.sieve:
    add     ecx, 4              ; index of current number whose multiples we remove
    cmp     ecx, 1268           ; sqrt(100000) * 4 rounded up
    je      .print
    cmp     [numArr + ecx], edx ; if 0, then it's not a prime
    jz      .sieve
    mov     eax, ecx            ; increase in index
    add     eax, 4              ; indexes start from 0, so increase needs to be bigger
    mov     ebx, ecx            ; index of inner loop
    add     ebx, eax            ; we don't want to set out prime to 0

.sieveLoop:

    mov     [numArr + ebx], edx ; set multiples of primes to 0
    add     ebx, eax            ; index of next multiple
    cmp     ebx, 400000         ; check if we removed all multiples
    jl      .sieveLoop          ; jl because primes doesn't have to divide 100,000
    jmp     .sieve

.print:
    mov     ecx, 0

.printLoop:
    add     ecx, 4              ; we skip 1, but it doesn't matter
    cmp     ecx, 400000
    je      .finished
    cmp     [numArr + ecx], edx ; if 0, skip
    jz      .printLoop
    mov     eax, [numArr + ecx]
    call    iprint
    mov     eax, space          ; space in between numbers to make output human readable
    call    sprint
    jmp     .printLoop

.finished:
    mov     eax, 0Ah            ; new line at the end
    push    eax
    mov     eax, esp
    call    sprint

    call    quit