all: compile
	@./zad3

compile:
	@nasm -f elf zad3.asm
	@ld -m elf_i386 zad3.o -o zad3

clean:
	rm zad3 zad3.o