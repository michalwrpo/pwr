all: compile
	@./zad4

compile:
	@nasm -f elf zad4.asm
	@gcc -m32 -no-pie zad4.o -o zad4

clean:
	rm zad4 zad4.o