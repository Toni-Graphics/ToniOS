typedef unsigned char byte;

extern "C" void setPixelA(int x, int y, byte color);



void setPixel(int x, int y, byte color) {
    setPixelA(x, y, color);
}