;
;*  $VER:       ammx_puts.asm 1.0
;*  $DATE:      2025-11-17 (2025-11-17)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_puts(const char *s);
;
; Description: calls the C library's puts() to print a string + newline.
; Input (s): RCX (first argument)
; Output: RAX = return value from puts
; -----------------------------------------------------------------------------

        global  ammx_puts
        extern  puts                ; declare external C library function

        section .text

ammx_puts:
        ; *** Function Prologue ***
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32             ; allocate shadow space

        ; RCX already has the string pointer (first argument)
        ; Just call puts() directly
        call    puts

        ; Return value from puts is already in RAX
        ; *** Epilogue ***
        add     rsp, 32
        pop     rbp
        ret
