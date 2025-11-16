;
;*   $VER:       ammx_fib.asm 1.0
;*   $DATE:      2025-11-16 (2025-11-16)
;*   $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   int64_t ammx_fib(int64_t)
;
; Description: calculates the Nth fibonacci number (Fib(n)).
; Input (n): RCX (first argument)
; Output (Fib(n)): RAX
; Assumes n >= 0.
; -----------------------------------------------------------------------------



section .text
global ammx_fib


ammx_fib:
    ; *** Function Prologue ***
    ; The stack pointer (RSP) must be 16-byte aligned before any CALL.
    ; Pushing RBP and allocating the shadow space (32 bytes) + local space maintains alignment.

    push    rbp                     ; Callee-saved: Save the base pointer (RBP) to the stack.
    mov     rbp, rsp                ; Callee-saved: Set RBP to the current stack pointer for a new stack frame.
    sub     rsp, 32                 ; Allocate 32 bytes for the shadow space (required by caller).

    ; *** Callee-Saved Register Preservation ***
    ; We'll use RBX, which is callee-saved, so we must save it.
    push    rbx                     ; Callee-saved: Save RBX to the stack. (Now RSP is RBP - 40)
                                    ; Note: RSP is NOT 16-byte aligned here (40 is not divisible by 16),
                                    ; but it will be fixed in the epilogue. This is typical for function setup.

    ; *** Base Cases ***
    cmp     rcx, 0                  ; Compare n (RCX) with 0.
    je      case_zero               ; Jump to case_zero if n == 0.

    cmp     rcx, 1                  ; Compare n (RCX) with 1.
    je      case_one                ; Jump to case_one if n == 1.

    ; *** Initialization for Iteration ***
    mov     rax, 0                  ; Initialize 'a' (Fib(i-2)) to 0. (F0)
    mov     rbx, 1                  ; Initialize 'b' (Fib(i-1)) to 1. (F1)
    
    ; Loop count is n-1, since we've handled F(0) and F(1).
    ; We start at i=2, and we loop n-1 times (from n down to 2).

loop_start:
    add     rax, rbx                ; New 'a' = old 'a' + 'b' (Fib(i) = Fib(i-2) + Fib(i-1)).
    xchg    rax, rbx                ; Swap 'a' and 'b': 'a' becomes old 'b', 'b' becomes new 'a' (Fib(i-1), Fib(i)).
                                    ; Now RAX holds the new Fib(i-1) and RBX holds the new Fib(i).
                                    ; The next iteration will use this new 'a' and 'b'.
    loop    loop_start              ; Decrement RCX and jump to loop_start if RCX is not zero.
                                    ; 'loop' instruction is a single-instruction loop control, using RCX implicitly.

    jmp     epilogue                ; Jump to the function epilogue.

case_zero:
    mov     rax, 0                  ; Fib(0) = 0.
    jmp     epilogue                ; Jump to the function epilogue.

case_one:
    mov     rax, 1                  ; Fib(1) = 1.
    jmp     epilogue                ; Jump to the function epilogue.

    ; *** Function Epilogue ***
epilogue:
    pop     rbx                     ; Callee-saved: Restore RBX from the stack.
    add     rsp, 32                 ; Deallocate the 32 bytes of shadow space.
    pop     rbp                     ; Callee-saved: Restore the base pointer (RBP).
    ret                             ; Return to the caller (result is in RAX).
