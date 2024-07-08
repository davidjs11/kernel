.PHONY: all run clean
all:
	@i386-elf-as -o boot.o -c src/boot.S
	@i386-elf-ld -o boot.bin boot.o -Ttext 0x7C00 --oformat=binary
	@cat boot.bin > boot.img

run: all
	@qemu-system-i386 boot.img

clean:
	@rm -rf boot.o boot.img boot.bin
