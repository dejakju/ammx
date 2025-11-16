;
;*  $VER:       ammx_fact.asm 1.0
;*  $DATE:      2025-11-16 (2025-11-16)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_fact(int64_t n)
;
; Description: calculates n! (factorial of n).
; Input (n): RCX (first argument)
; Output (ammx_fact(n)): RAX
; Assumes n >= 0 and fits in int64_t.
; -----------------------------------------------------------------------------

        global  ammx_fact
        section .text

ammx_fact:
        ; *** Function Prologue ***
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32                ; shadow space
        push    rbx                    ; save RBX (callee-saved)

        ; *** Base Cases ***
        cmp     rcx, 0
        je      case_zero              ; 0! = 1

        ; *** Initialization ***
        mov     rax, 1                 ; result accumulator
        mov     rbx, rcx               ; counter = n

loop_start:
        imul    rax, rbx               ; result *= counter
        dec     rbx                    ; counter--
        jnz     loop_start             ; repeat until counter == 0

        jmp     epilogue

case_zero:
        mov     rax, 1                 ; 0! = 1

epilogue:
        pop     rbx
        add     rsp, 32
        pop     rbp
        ret
