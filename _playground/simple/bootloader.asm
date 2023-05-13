; bootloader.asm
; Assemble with: nasm -f elf32 -o bootloader.o bootloader.asm

section .text
bits 16
global start
extern setPixel
; extern _set_pixel_asm

start:
    ; Set up stack
    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    ; switch to 320x200 vga mode
    mov ax, 0x0013    ;    move the number of the mode to ax
    int 10h    ;    and enter the mode using int 10h

    ; Call C function setPixel
    call setPixel


    ; ; Example of calling _set_pixel_asm directly

    ; ; Inititialize loop counter
    ; mov ax, 0
    ; draw:
    ; ;Set the parameters on the stack (push them in reverse order)
    ;     push 0x28 ; col
    ;     push ax ; y
    ;     push ax ; x

    ;     call _set_pixel_asm

    ;     ; Clean up the stack after the call (pop the parameters)
    ;     ; TODO: Is that necessary? It works with and without the next line.
    ;     ; Might this lead to a stack overflow, if not cleaned up?
    ;     ;add sp, 6 ; 6 bytes = 3 parameters * 2 bytes each (because we're in 16bit real mode)

    ;     add ax, 1
    ;     cmp ax, 128
    ;     jle draw

    ; Infinite loop
    cli
.hang:
    hlt
    jmp .hang


; Note: This is done by the linker.ld script now
; Bootloader padding and signature
; times 510-($-$$) db 0
; dw 0xAA55
