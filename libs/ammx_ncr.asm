;
;*  $VER:       ammx_ncr.asm 1.0
;*  $DATE:      2025-11-16 (2025-11-16)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_ncr(int64_t n, int64_t r)
;
; Description: calculates the binomial coefficient nCr (combinations without repetition).
; Input: RCX = n, RDX = r
; Output: RAX = nCr
; Assumes 0 <= r <= n and results fit in int64_t.
; -----------------------------------------------------------------------------

        global  ammx_ncr
        extern  ammx_fact              ; factorial helper (int64_t ammx_fact(int64_t))

        section .text

ammx_ncr:
        ; *** Prologue ***
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32                ; shadow space
        push    rbx                    ; save RBX

        ; --- Compute n! ---
        mov     rcx, rcx               ; RCX already has n
        call    ammx_fact
        mov     rbx, rax               ; save n! in RBX

        ; --- Compute r! ---
        mov     rcx, rdx               ; RCX = r
        call    ammx_fact
        mov     r8, rax                ; save r! in R8

        ; --- Compute (n-r)! ---
        mov     rcx, rcx               ; RCX = n (still in RCX? careful!)
        sub     rcx, rdx               ; RCX = n - r
        call    ammx_fact
        mov     r9, rax                ; save (n-r)! in R9

        ; --- Compute denominator r! * (n-r)! ---
        mov     rax, r8
        imul    rax, r9                ; r! * (n-r)!

        ; --- Divide n! / (r! * (n-r)!) ---
        mov     rdx, 0                 ; clear high part for signed division
        mov     rcx, rax               ; denominator in RCX
        mov     rax, rbx               ; numerator = n!
        idiv    rcx                    ; RAX = n! / (r! * (n-r)!)

        ; --- Epilogue ---
        pop     rbx
        add     rsp, 32
        pop     rbp
        ret
