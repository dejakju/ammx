;
;*   $VER:       ammx_build.asm 1.2
;*   $DATE:      2025-11-13 (2025-11-15)
;*   $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; A 64-bit function that returns the maximum value of its three 64-bit integer
; arguments. The function has signature:
;
;   viod ammx_build()
;
; Calling convention: Microsoft x64 (first four integer/pointer arguments passed in RCX, RDX, R8, R9)
; Note that the parameters have already been passed in rcx, rdx, and r8. We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

    global  ammx_build
    extern  printf

    section .text

ammx_build:
    sub     rsp, 20h

    lea     rcx, [rel fmt]
    lea     rdx, [rel date]
    lea     r8, [rel time]
    lea     r9, [rel nasm]
    call    printf

    add     rsp, 20h

    xor     rax, rax
    ret

    section .data
fmt:    db  "(compiled: %s, %s - powered by nasm %s)", 10, 0
date:   db  __?DATE?__, 0
time:   db  __?TIME?__, 0
nasm:   db  __?NASM_VER?__, 0
