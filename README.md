# OS

Why do I need a Cross Compiler?
https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F

x86 assembly instruction reference
https://www.felixcloutier.com/x86/


Calling asm from C:
https://www.reddit.com/r/osdev/comments/xbu135/calling_asm_function_from_c/

There are two main ways to access/call asm from c:

One way is by using inline assembly which allows you to directly embed asm inside your c code. There are plenty of tutorials out there (assuming you are using GCc), just google it.

You can also define a function entirely in assembly (I.e. in a separate source file, usually .s or .S) and use it from c like any other function: declare the function prototype as if it were a c function and you should be good to go.

Some things to keep in mind however:

Be aware of Name mangling (this shouldn’t be a problem if using Linux and cdecl (the default calling convention))
depending on your assembler you might need to declare Labels extern, otherwise they won’t be visible outside of the file (with NASM that’s the case)
depending on the calling convention, the compiler expects certain registers to remain intact after a function was called, make sure to keep that in mind, otherwise you’ll most likely get weird behavior
void functions taking no arguments are pretty straightforward, just declare them and you’re good to go. If you however want to pass parameters to and from the function you’ll have to conform to whatever calling convention you’re using (probably cdecl) and make correct use of the stack/the registers

Debugging

GDB personal cheatsheet
https://liodeus.github.io/2020/11/13/GDB.html

make debug
gdb bootloader.o
target remote localhost:1234
set architecture i8086
break *0x7c00 or break *setPixel


Disassembling
Disassemble in 16Bit mode:
i386-elf-objdump -Mi8086 -d bootloader.o
Disassembling 16bit code without this parameter will result in garbage (e.g. missing instructions, wrong labels, ...)


