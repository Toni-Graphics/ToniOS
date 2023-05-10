# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = gcc
CFLAGS = -m32 -Isrc/ -Isrc/lib/ -std=gnu99 -ffreestanding -O1 -Wall -Wextra

VM = qemu-system-x86_64
VM_FLAGS = -cdrom

AS = as
ASFLAGS = --32 #-f elf64
LD = ld
LDFLAGS = -m elf_i386 -T linker.ld  -nostdlib 

TARGET = iso/ToniOs.iso
SRCDIR = src
ISODIR = isodir
BINDIR = bin

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
$(BINDIR)/OS.bin: $(OBJDIR)/boot.o $(OBJDIR)/kernel.o | create_directories
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/boot.o: $(SRCDIR)/boot.s | create_directories
	$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR)/kernel.o: $(SRCDIR)/kernel/kernel.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(BINDIR)/OS.bin
	mkdir -p $(ISODIR)/boot/grub
	cp $< $(ISODIR)/boot/OS.bin
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

run: $(TARGET)
	$(VM) $(VM_FLAGS) $<

create_directories:
	@mkdir -p $(OBJDIR) $(BINDIR) $(ISODIR) iso

clean:
	rm -rf $(ISODIR) $(BINDIR) $(ISODIR)