; VGA 320x200 bootloader example
; Assemble with: nasm -f bin -o bootloader.bin bootloader.asm

bits 16
org 0x7C00

start:
    ; Set up stack
    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Set video mode to 320x200
    mov ah, 0x00
    mov al, 0x13
    int 0x10

    ; Draw a pixel at (x, y) with color
    mov ax, 0xA000
    mov es, ax
    xor di, di

    ; Set (x, y) and color
    mov cx, 100 ; x
    mov dx, 50  ; y
    mov al, 0x0F ; White

    ; Calculate the offset: offset = y * 320 + x
    imul dx, 320
    add dx, cx

    ; Write the pixel
    mov di, dx
    mov es:[di], al

    ; Infinite loop
    cli
.hang:
    hlt
    jmp .hang

; Bootloader padding and signature
times 510-($-$$) db 0
dw 0xAA55
