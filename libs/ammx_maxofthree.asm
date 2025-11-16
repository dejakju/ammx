;
;*  $VER:       ammx_maxofthree.asm 1.2
;*  $DATE:      2025-10-28 (2025-11-16)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_maxofthree(int64_t x, int64_t y, int64_t z)
;
; Description: return the greatest of the three numbers (x,y,z).
; Input (x): RCX (first argument)
; Input (y): RDX (second argument)
; Input (z): R8 (third argument)
; Output (ammx_maxofthree(x,y,z)): RAX
; Assumes x, y, z are all of valid int64_t type.
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
