;
;*  $VER:       ammx_increment.asm 1.0
;*  $DATE:      2025-10-28 (2025-10-28)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_increment(int64_t x)
;
; Description: increments the provided value by one.
; Input (x): RCX (the number to be incremented)
; Output (ammx_increment(x)): RAX
; Assumes x is of valid int64_t type.
; -----------------------------------------------------------------------------

        global  ammx_increment
        section .text

ammx_increment:
        mov     rax, rcx                ; result (rax) initially holds x
        inc     rax                     ; increment the result
        ret                             ; return the result in rax
