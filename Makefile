# https://stackoverflow.com/questions/18416564/how-to-resolve-crt0-o-linking-issue-in-cross-compiling
# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = x86_64-elf-g++ #g++
CFLAGS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

AS = nasm
ASFLAGS = -f elf32 #-f elf64
LD = x86_64-elf-ld #ld
LDFLAGS = -m elf_x86_64 -Ttext 0x0 --oformat binary

TARGET = boot
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
$(BINDIR)/kernel.bin: $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o $(OBJDIR)/tty.o $(OBJDIR)/graphics.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

$(OBJDIR)/kernel_entry.o: $(SRCDIR)/kernel_entry.asm | create_directories
	nasm $< -f elf32 -o $@

$(OBJDIR)/kernel.o: $(SRCDIR)/kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

# Rule to disassemble the kernel - may be useful to debug
$(OBJDIR)/kernel.dis: $(BINDIR)/kernel.bin
	ndisasm -b 32 $< > $@

$(BINDIR)/bootsect.bin: $(SRCDIR)/bootsect.asm | create_directories
	$(AS) $(ASFLAGS) $< -f bin -o $@

$(OBJDIR)/tty.o: src/tty.asm
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR)/graphics.o: src/graphics.asm
	$(AS) $(ASFLAGS) -o $@ $<

$(BINDIR)/os-image.bin: $(BINDIR)/bootsect.bin $(BINDIR)/kernel.bin
	cat $^ > $@

run: $(BINDIR)/os-image.bin
# qemu-system-x86_64 -fda $<
	qemu-system-i386 -fda $<

create_directories:
	@mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)


