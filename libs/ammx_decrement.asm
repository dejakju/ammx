;
;*   $VER:       ammx_decrement.asm 1.0
;*   $DATE:      2025-10-28 (2025-10-28)
;*   $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_decrement(int64_t x)
;
; Description: decrements the provided value by one.
; Input (x): RCX (the number to be decremented)
; Output (ammx_decrement(x)): RAX
; Assumes x is of valid int64_t type.
; -----------------------------------------------------------------------------

        global  ammx_decrement
        section .text

ammx_decrement:
        mov     rax, rcx                ; result (rax) initially holds x
        dec     rax                     ; decrement the result
        ret                             ; return the result in rax
