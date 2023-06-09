# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = gcc
CFLAGS = -m32 -Ilibc/include/ -Idrivers/Vga/include/ -Idrivers/ -I. -Ilibc/ -Idrivers/fs/include -Idrivers/Key/include -std=gnu99  -ffreestanding -O0  -Waddress  -Wall  -Wextra

VM = qemu-system-x86_64
VM_FLAGS = -cdrom

AS = nasm
ASFLAGS = -f elf32 #--32 
LD = ld
LDFLAGS = -m elf_i386 -T linker.ld  -nostdlib 

TARGET = iso/ToniOs.iso
SRCDIR = src
ISODIR = isodir
BINDIR = bin
OBJDIR = obj

# First rule is the one executed when no parameters are fed to the Makefile
all: build

# Notice how dependencies are built as needed
$(BINDIR)/OS.bin: $(OBJDIR)/boot.o     $(OBJDIR)/kernel.o $(OBJDIR)/stdio.o  $(OBJDIR)/stdlib.o   $(OBJDIR)/string.o   $(OBJDIR)/io.o	    \
				  $(OBJDIR)/key.o      $(OBJDIR)/vga.o    $(OBJDIR)/ata.o    $(OBJDIR)/graphics.o $(OBJDIR)/math.o     $(OBJDIR)/locale.o    \
				  $(OBJDIR)/x86_asm.o  $(OBJDIR)/x86.o    $(OBJDIR)/isr.o    $(OBJDIR)/gdt.o      $(OBJDIR)/syscall.o  $(OBJDIR)/register.o  \
				  $(OBJDIR)/timer.o    $(OBJDIR)/sys.o    $(OBJDIR)/pci.o    $(OBJDIR)/tfs_lba.o  $(OBJDIR)/tfs_file.o $(OBJDIR)/tfs_dir.o   | create_directories
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/boot.o: kernel/boot/boot.asm | create_directories
	$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR)/kernel.o: kernel/kernel.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/stdio.o: libc/src/stdio.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/stdlib.o: libc/src/stdlib.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/string.o: libc/src/string.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/io.o: drivers/io.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/key.o: drivers/Key/src/key.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/vga.o: drivers/VGA/src/vga.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/ata.o: drivers/ata/ata.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/graphics.o: drivers/VGA/src/graphics.asm
	$(AS) $< $(ASFLAGS) -o $@ 

$(OBJDIR)/math.o: libc/src/math.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/locale.o: libc/src/locale.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/x86_asm.o: libc/x86/x86.asm
	$(AS)  $<  $(ASFLAGS) -o $@ 

$(OBJDIR)/x86.o: libc/x86/x86.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/isr.o: libc/isr/src/isr.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/gdt.o: libc/gdt/gdt.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/syscall.o: libc/syscall/src/syscall.c
	$(CC) -c $< -o $@ $(CFLAGS) -mno-80387

$(OBJDIR)/register.o: libc/register/reg.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/timer.o: libc/timer/timer.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/sys.o: libc/src/sys.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/pci.o: drivers/pci/pci.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/tfs_lba.o: fs/Tfs/lba.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/tfs_file.o: fs/Tfs/file.c 
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/tfs_dir.o: fs/Tfs/dir.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(BINDIR)/OS.bin
	@mkdir -p $(ISODIR)/boot/grub
	@cp $< $(ISODIR)/boot/OS.bin
	@cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	@grub-mkrescue -o $@ isodir

build: $(TARGET)
	@echo ''

run: $(TARGET)
	@$(VM) $(VM_FLAGS) $<

create_directories:
	@mkdir -p $(OBJDIR) $(BINDIR) $(ISODIR) iso

clean:
	@rm -rf $(ISODIR) $(BINDIR) $(ISODIR) $(OBJDIR)