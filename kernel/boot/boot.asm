section .multiboot
    align 4
    dd 0x1BADB002     ; Multiboot magic number
    dd 0              ; Flags
    dd -(0x1BADB002 + 0) ; Checksum (negative sum of all fields)

section .text
    global _start
    extern kmain

_start:
    ; Set up the stack
    mov esp, stack_top

    ; Call the bootloader entry point
    call bootloader_entry

    ; Loop or halt system after kernel execution
    cli
    hlt

bootloader_entry:
    ; Set up segment registers
    ;xor eax, eax
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    ;mov ss, ax

    ; Load the Multiboot2 information structure address into ebx
    mov ebx, [esp + 4]

    ; Call the kernel entry point (kmain)
    call kmain

    ; Jump back to the bootloader entry point
    ret

section .bss
    stack resb 8192
stack_top:
