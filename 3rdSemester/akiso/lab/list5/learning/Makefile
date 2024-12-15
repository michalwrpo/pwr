test: test_compile
	@./test

test_compile:
	@nasm -f elf test.asm
	@ld -m elf_i386 test.o -o test

fizz: fizz_compile
	@./fizzbuzz

fizz_compile:
	@nasm -f elf fizzbuzz.asm
	@ld -m elf_i386 fizzbuzz.o -o fizzbuzz