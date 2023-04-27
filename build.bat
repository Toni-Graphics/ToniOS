@echo off

nasm -f elf src/kernel/graphics.asm -o bin/graphics.o
nasm src/boot.asm -f elf -o bin/b.o

g++ -m16 src/kernel/boot.cpp bin/graphics.o  -ffreestanding -o bin/c.o

ld -T NUL  -o bin/image.tmp -Ttext 0x0 bin/c.o bin/b.o

objcopy -O binary -j .text bin/image.tmp bin/image.bin
