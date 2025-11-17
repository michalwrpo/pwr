parser: lex.yy.c parser.tab.c
	gcc -o parser lex.yy.c parser.tab.c -lfl -lm

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y -Wcounterexamples

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean:
	rm -f parser lex.yy.c parser.tab.c parser.tab.h
