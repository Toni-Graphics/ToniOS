typedef unsigned char byte;

//extern "C" void
extern void _switchTo320x200();
extern void _set_pixel_asm(int x, int y, byte color);
