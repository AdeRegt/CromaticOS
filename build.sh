nasm -felf32 boot.asm -o boot.o
gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -m32 
if grub-file --is-x86-multiboot myos.bin; then
	echo "de kernel is juist gecompileerd"
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso
else
	echo "de kernel is niet juist gecompiled"
fi
