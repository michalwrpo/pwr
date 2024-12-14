all: compile
	@./zad1

compile:
	@nasm -f elf zad1.asm
	@ld -m elf_i386 zad1.o -o zad1

clean:
	rm zad1 zad1.o