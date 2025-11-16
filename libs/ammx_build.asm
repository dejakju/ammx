;
;*   $VER:       ammx_build.asm 1.2
;*   $DATE:      2025-11-13 (2025-11-15)
;*   $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   void ammx_build()
;
; Description: prints the build date/time and nasm version to stdout.
; Input: void
; Output: void
; Note: A newline terminator is added to the output - beware
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
