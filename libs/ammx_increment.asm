;
;*   $VER:       ammx_increment.asm 1.0
;*   $DATE:      2025-10-28 (2025-10-28)
;*   $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; A 64-bit function that returns the value increased by one.
; The function has signature:
;
;   int64_t ammx_increment(int64_t x)
;
; Calling convention: Microsoft x64 (first four integer/pointer arguments passed in RCX, RDX, R8, R9)
; Note that the parameters have already been passed in rcx, rdx, and r8. We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

        global  ammx_increment
        section .text

ammx_increment:
        mov     rax, rcx                ; result (rax) initially holds x
        inc     rax                     ; increment the result
        ret                             ; return the result in rax
