;
;*  $VER:       ammx_getchar.asm 1.0
;*  $DATE:      2025-11-17 (2025-11-17)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_getchar(void);
;
; Description: calls the C library's getchar() to read one character from stdin.
; Output: RAX = character read, or EOF (-1) on error
; Note: The integer is promoted to an int64_t.
; -----------------------------------------------------------------------------

        global  ammx_getchar
        extern  getchar              ; declare external C library function

        section .text

ammx_getchar:
        ; *** Function Prologue ***
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32              ; allocate shadow space

        ; Call getchar() directly (no arguments)
        call    getchar

        ; Return value from getchar is already in RAX
        ; *** Epilogue ***
        add     rsp, 32
        pop     rbp
        ret
