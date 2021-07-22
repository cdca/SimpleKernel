#!/bin/bash

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

rm *.o
rm os.bin
rm -r -f isodir

nasm -felf32 boot.asm -o boot.o
#i686-elf-as boot.s -o boot.o
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c isr.c -o isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c common.c -o common.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c keyboard.c -o keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c pic.c -o pic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c monitor.c -o monitor.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c timer.c -o timer.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c rtc.c -o rtc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o isr.o idt.o gdt.o common.o pic.o monitor.o keyboard.o timer.o -lgcc
grub-file --is-x86-multiboot os.bin
if grub-file --is-x86-multiboot os.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
rm -r isodir
mkdir -p isodir/boot/grub
cp os.bin isodir/boot/os.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o os.iso isodir --xorriso=./xorriso/xorriso-1.4.6/xorriso/xorriso
qemu-system-i386 -cdrom os.iso

#rm *.o
#rm -r -f isodir
