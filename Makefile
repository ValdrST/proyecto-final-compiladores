all: 
	bison -vd yacc_p.y
	echo "#include \"attribs.h\"" > encabezado.txt
	cat yacc_p.tab.h >> encabezado.txt
	cat encabezado.txt > yacc_p.tab.h
	flex lex.l
	gcc -g -std=c99 -c -o intermediate_code.o intermediate_code.c
	gcc -g -std=c99 -c -o tablaSimbol.o tablaSimbol.c
	gcc -g -std=c99 -c -o pilaTablaSimbol.o pilaTablaSimbol.c
	gcc -g -std=c99 -c -o tablaTipo.o tablaTipo.c
	gcc -g -std=c99 -c -o pilaTablaTipo.o pilaTablaTipo.c
	gcc -g -std=c99 -c -o attribs.o attribs.c
	gcc -g -std=c99 -c -o cMips.o cMips.c
	gcc -g -std=c99 -o p tablaTipo.o attribs.o tablaSimbol.o intermediate_code.o pilaTablaSimbol.o pilaTablaTipo.o cMips.o yacc_p.tab.c lex.yy.c -lfl

clean:
	rm -f p
	rm -f *.yy.c
	rm -f *.output
	rm -f *.tab.h
	rm -f *.tab.c
	rm -f *.o
	rm -f encabezado.txt