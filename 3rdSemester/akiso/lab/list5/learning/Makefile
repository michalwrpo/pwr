
fizz: fizz_compile
	@./fizzbuzz

fizz_compile:
	@nasm -f elf fizzbuzz.asm
	@ld -m elf_i386 fizzbuzz.o -o fizzbuzz