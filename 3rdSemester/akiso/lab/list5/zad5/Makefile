all: compile
	@./mandelbrot

compile:
	@nasm -f elf mandelbrot.asm
	@ld -m elf_i386 mandelbrot.o -o mandelbrot

clean:
	rm mandelbrot mandelbrot.o