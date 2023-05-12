extern "C" void _set_pixel_asm(int x, int y, unsigned char color);

extern "C" void setPixel() {
    int x = 0;
    int y = 0;
    unsigned char color = 0x28;
    for (x = 0;x<128; x++) {
      _set_pixel_asm(x, x, color);
    }
}
