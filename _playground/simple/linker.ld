ENTRY(start)

SECTIONS
{
    . = 0x7C00;

    .text : {
        *(.text)
    }

    /* C/C++ code and data */
    .c_code : {
        *(.text.*)
        *(.rodata.*)
        *(.data.*)
    }

    /* Align the stack to a 16-byte boundary */
    . = ALIGN(16);

    /* Define the stack location */
    stack_top = .;

    .sig : AT(0x7DFE) {
        SHORT(0xAA55);
    }
}