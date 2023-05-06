#include "./tty.h"
#include "./graphics.h"

/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
    //console_out();
    // say hello. Note: we do not see this message because we are switching to vga mode in the next line.
    _console_out_asm();

    // switch to 320x200 vga mode to draw some pixels
    _switchTo320x200();

    int x = 10;
    int y = 10;
    unsigned char color = 0x28;

    _set_pixel_asm(x, x, color);

    // This does not work correctly, I don't know why yet.
    // The stack seems to be used correctly, if I call _set_pixel_asm directly in an assembly loop, everything works fine (see example in _playground/simple/bootloader.asm)
    // for (x = 0;x<128; x++) {
    //   _set_pixel_asm(x, x, color);
    // }

}
