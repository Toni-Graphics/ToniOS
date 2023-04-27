
section .text

global _setPixelA
_setPixelA:
    push ebp

    mov ebp, esp

    mov ah, 0x0c
    mov al, [ebp+8]   
    mov bh, 0

    mov cx, [ebp+12]
    mov dx, [ebp+16]

    int 0x10

    pop ebp

    ret