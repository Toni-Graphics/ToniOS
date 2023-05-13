# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Variables
NASM = nasm
GXX = i386-elf-g++ #g++
LD = i386-elf-ld #ld
NASMFLAGS = -f elf32 -g
GXXFLAGS = -m32 -ggdb -ffreestanding -fno-exceptions -fno-rtti -nostdlib -c
LDFLAGS = -m elf_i386 -ggdb -T linker.ld --oformat binary
#LDFLAGS = -m elf_i386 -Ttext 0x7C00 --oformat binary

# Targets
all: run

bootloader.bin: bootloader.o main.o set_pixel.o
	$(LD) $(LDFLAGS) -o $@ $^

bootloader.o: bootloader.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

main.o: main.cpp
	$(GXX) $(GXXFLAGS) -o $@ $<

set_pixel.o: set_pixel.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

run: bootloader.bin
	qemu-system-i386 -drive format=raw,file=$<,index=0,media=disk

debug: bootloader.bin
	qemu-system-i386 -s -S -drive format=raw,file=$<,index=0,media=disk

clean:
	rm -f *.o *.bin
