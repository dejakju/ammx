;
;*   $VER:       ammx_maxofthree.asm 1.1
;*   $DATE:      2025-10-28 (2025-11-15)
;*   $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; A 64-bit function that returns the maximum value of its three 64-bit integer
; arguments. The function has signature:
;
;   int64_t ammx_maxofthree(int64_t x, int64_t y, int64_t z)
;
; Calling convention: Microsoft x64 (first four integer/pointer arguments passed in RCX, RDX, R8, R9)
; Note that the parameters have already been passed in rcx, rdx, and r8. We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

        global  ammx_maxofthree
        section .text

ammx_maxofthree:
        mov     rax, rcx                ; result (rax) initially holds x
        cmp     rax, rdx                ; is x less than y?
        cmovl   rax, rdx                ; if so, set result to y
        cmp     rax, r8                 ; is max(x,y) less than z?
        cmovl   rax, r8                 ; if so, set result to z
        ret                             ; the max will be in rax
