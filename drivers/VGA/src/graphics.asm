bits 32

section .text

global _set_pixel_asm

_set_pixel_asm:
  push bp
  mov bp, sp


  ; Save registers that will be modified
  ; Note: Depending on the calling convention, the compiler expects certain registers
  ; to remain intact after a function was called, make sure to keep that in mind, otherwise you’ll most likely get weird behavior
  pusha

  mov ax, 0xA000
  mov es, ax
  xor di, di

  ; Get arguments
  mov cx, [bp + 4]  ; x
  mov dx, [bp + 6]  ; y
  mov ax, [bp + 8] ; color

  ; Calculate the offset: offset = y * 320 + x
  imul dx, 320
  add dx, cx

  ; Write the pixel
  mov di, dx
  mov es:[di], al

  ; Restore the saved registers
  popa

  ; Restore the original base pointer value and return
  mov sp, bp
  pop bp

  ret