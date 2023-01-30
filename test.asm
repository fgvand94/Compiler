bits 64

default rel

;segment .data stores static and global data. 
segment .data
;msg equivalent to memory location of first byte of a string db is data
;byte-somespace- the oxd,0xa Are related to asc 2 and I guess make the
;next thing printed on a new line. 
    msg db "Hello world!", 0xd, 0xa, 0

;segment .text is the segment with executable instructions.
segment .text
; global main makes the symbol main visible on the global scope/linker
; so that you can make it an entry point.
global main
;extern is a message to the assembler-pseudoinsctruction- it's meant
; to get external functions like header files in c++
extern ExitProcess

extern printf

main:
;rbp point to the base of the current stack frame by convention
;rsp point the the top of the current stack frame by convention


    lea     rcx, [msg]
    call    printf

    xor     rax, rax
    call    ExitProcess