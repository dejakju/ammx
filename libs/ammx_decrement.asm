; -----------------------------------------------------------------------------
; A 64-bit function that returns the value decreased by one.
; The function has signature:
;
;   int64_t ammx_decrement(int64_t x)
;
; Calling convention: Microsoft x64 (first four integer/pointer arguments passed in RCX, RDX, R8, R9)
; Note that the parameters have already been passed in rcx, rdx, and r8. We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

        global  ammx_decrement
        section .text

ammx_decrement:
        mov     rax, rcx                ; result (rax) initially holds x
        dec     rax                     ; decrement the result
        ret                             ; return the result in rax
