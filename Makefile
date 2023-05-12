# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = gcc
CFLAGS = -m32 -Ilibc/include/ -Idrivers/Vga/include/ -I. -Idrivers/fs/include -Idrivers/Key/include -std=gnu99 -ffreestanding -O1 -Waddress -Wall # -Wextra

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
all: run clean

# Notice how dependencies are built as needed
$(BINDIR)/OS.bin: $(OBJDIR)/boot.o $(OBJDIR)/kernel.o | create_directories
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/boot.o: kernel/boot/boot.s | create_directories
	$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR)/kernel.o: kernel/kernel.c libc/src/*.c drivers/VGA/src/*.c drivers/Key/src/*.c drivers/fs/src/*.c
	$(CC) -c $^ -o $@ $(CFLAGS)

$(TARGET): $(BINDIR)/OS.bin
	@mkdir -p $(ISODIR)/boot/grub
	@cp $< $(ISODIR)/boot/OS.bin
	@cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

run: $(TARGET)
	$(VM) $(VM_FLAGS) $<

create_directories:
	@mkdir -p $(OBJDIR) $(BINDIR) $(ISODIR) iso

clean:
	@rm -rf $(ISODIR) $(BINDIR) $(ISODIR)