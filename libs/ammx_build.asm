;
;*  $VER:       ammx_build.asm 1.5
;*  $DATE:      2025-11-16 (2025-11-16)
;*  $AUTHOR:    Goran (dejakju@gmail.com)
;
; -----------------------------------------------------------------------------
; The functions' C signature:
;
;   char* ammx_build()
;
; Description: Formats the build date/time and nasm version into a dynamic string.
; Input: void
; Output: RAX (char* pointer to the heap-allocated string)
; Note: The caller MUST free the returned pointer.
; -----------------------------------------------------------------------------

    global  ammx_build
    extern  sprintf         
    extern  malloc          
    
    section .text

ammx_build:
    ; --- 1. Prologue & Callee-Saved Register Save ---
    sub     rsp, 20h                ; Windows x64 ABI: Shadow space (32 bytes).
    push    rbx                     ; **FIX:** Save RBX (Non-Volatile) to the stack.

    ; --- 2. Allocate Memory (malloc) ---
    mov     rcx, 80h                ; 1st arg (size): Request 128 bytes (80h).
    call    malloc                  ; Call malloc(128). Result (buffer pointer) is in RAX.
    
    ; --- Error Check ---
    cmp     rax, 0                  ; Check if malloc failed (RAX == NULL)
    je      epilogue_error_no_free  
    
    ; --- FIX: Save Pointer to Non-Volatile Register ---
    mov     rbx, rax                ; **FIX:** Save the buffer pointer (RAX) into RBX (safe across calls).

    ; --- 3. Format String (sprintf) ---
    ; Arguments: str (RCX), format (RDX), arg1 (R8), arg2 (R9), arg3 (Stack)
    
    mov     rcx, rbx                ; 1st arg (str): Pointer to the allocated buffer (from RBX).
    lea     rdx, [rel fmt]          ; 2nd arg (format): Pointer to the format string.
    lea     r8,  [rel date]         ; 3rd arg (...): Date string.
    lea     r9,  [rel time]         ; 4th arg (...): Time string.
    
    ; 5th argument setup (must be on the stack)
    lea     r11, [rel nasm]         ; Load pointer to 'nasm' string into R11.
    mov     [rsp+20h], r11          ; 5th argument in proper stack slot
    
    ; Variadic Function: Set AL to 0 (Mandatory for sprintf)
    xor     al, al                  ; Sets AL=0.
    
    call    sprintf                 ; Call sprintf.

    ; --- 4. Prepare Return Value and Epilogue ---
    mov     rax, rbx                ; Restore the buffer pointer (char*) into RAX for return.
    jmp     epilogue_return

epilogue_error_no_free:
    xor     rax, rax                ; Ensure RAX is 0 (NULL).
    
epilogue_return:
    pop     rbx                     ; **FIX:** Restore the original value of RBX.
    add     rsp, 20h                ; Restore stack pointer (deallocate shadow space).
    ret                             ; Return (RAX holds the allocated string pointer).

    section .data
fmt:    db  "(compiled: %s, %s - powered by nasm %s)", 0
date:   db  __?DATE?__, 0
time:   db  __?TIME?__, 0
nasm:   db  __?NASM_VER?__, 0
