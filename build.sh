#!/bin/bash

mkdir bin

# assemble boot.s file
as --32 src/boot.s -o bin/boot.o

# compile kernel.c file
gcc -m32 -c src/kernel/kernel.c  -o bin/kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# linking all the object files to OS.bin
ld -m elf_i386 -T linker.ld bin/boot.o bin/kernel.o  -o bin/OS.bin -nostdlib

# check OS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot bin/OS.bin

# building the iso file
mkdir -p isodir/boot/grub
cp bin/OS.bin isodir/boot/OS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o iso/ToniOS.iso isodir

#cleaning
rm bin/*.o
rm bin/*.bin
rmdir bin
rm -r isodir

# run it in qemu
qemu-system-x86_64 -cdrom iso/ToniOS.iso
