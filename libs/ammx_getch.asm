;
;*  $VER:       ammx_getch.asm 1.0
;*  $DATE:      2025-11-17 (2025-11-17)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_getch(void);
;
; Description: calls the C library's getch() to read one key immediately.
; Output: RAX = character read
; -----------------------------------------------------------------------------

        global  ammx_getch
        extern  getch                ; declare external C library function

        section .text

ammx_getch:
        ; *** Function Prologue ***
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32              ; allocate shadow space

        ; Call getch() directly (no arguments)
        call    getch

        ; Return value from getch is already in RAX
        ; *** Epilogue ***
        add     rsp, 32
        pop     rbp
        ret
