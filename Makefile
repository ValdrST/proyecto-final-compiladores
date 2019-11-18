all: 
	bison -vd yacc.y
	echo "#include \"attribs.h\"" > temp.h
	cat yacc.tab.h >> temp.h
	cat encabezado.txt > yacc.tab.h
	flex lex.l
	gcc -g -std=c99 -c -o intermediate_code.o intermediate_code.c
	gcc -g -std=c99 -c -o symbols.o symbols.c
	gcc -g -std=c99 -c -o types.o types.c
	gcc -g -o p intermediate_code.o symbols.o types.o attribs.h yacc.tab.c lex.yy.c -lfl

clean:
	rm -f p
	rm -f *.yy.c
	rm -f *.output
	rm -f *.tab.h
	rm -f *.tab.c
	rm -f *.o
	rm -f encabezado.txt