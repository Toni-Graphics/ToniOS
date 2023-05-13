# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = gcc
CFLAGS = -m32 -Ilibc/include/ -Idrivers/Vga/include/ -Idrivers/ -I. -Idrivers/fs/include -Idrivers/Key/include -std=gnu99 -ffreestanding -O1 -Waddress -Wall # -Wextra

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
OBJDIR = obj

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
$(BINDIR)/OS.bin: $(OBJDIR)/boot.o $(OBJDIR)/kernel.o $(OBJDIR)/stdio.o $(OBJDIR)/stdlib.o $(OBJDIR)/string.o $(OBJDIR)/io.o	\
				  $(OBJDIR)/key.o  $(OBJDIR)/vga.o    $(OBJDIR)/fs_low.o | create_directories
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/boot.o: kernel/boot/boot.s | create_directories
	$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR)/kernel.o: kernel/kernel.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/stdio.o: libc/src/stdio.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/stdlib.o: libc/src/stdlib.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/string.o: libc/src/string.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/io.o: drivers/io.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/key.o: drivers/Key/src/key.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/vga.o: drivers/VGA/src/vga.c
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/fs_low.o: drivers/fs/src/low.c
	$(CC) -c $<  -o $@ $(CFLAGS)

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
	@rm -rf $(ISODIR) $(BINDIR) $(ISODIR) $(OBJDIR)