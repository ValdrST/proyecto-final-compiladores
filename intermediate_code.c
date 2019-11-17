#include "intermediate_code.h"
#include <stdio.h>
#include <stdlib.h>

/* Funcion encargada de inicializar la tabla de cuadruplas. */
void init_code(){
	CODE.items = malloc(sizeof(quad) * 1000);
	CODE.i =0;
}

/* Funcion encargada de llenar la tabla con cuadruplas. */
int gen_code(char *op , char *arg1, char *arg2, char *res){
	quad q;
	q.op = op;
	q.arg1 = arg1;
	q.arg2 = arg2;
	q.res = res;
	*(CODE.items + CODE.i) = q;
	CODE.i++;
	return CODE.i -1;
}

/* Funcion que crea una lista dentro de una etiqueta. */
label create_list(int l){
	label list;
	list.items = malloc(sizeof(int) * 100);
	list.i = 0;
	list.items[list.i] = l;
	list.i++;
	return list;
}

/* Funcion encargadad de copiar las listas de ambas etiquetas. */
label merge(label l1, label l2){
	label l;
	l = l1;
	for(int i = 0; i < l2.i; i++){
		l.items[l.i] = l2.items[i];
		l.i++;
	}
	return l;
}

/* Funcion encargada de cambiar la localizacion donde se almacenara el resultado. */
void backpatch(label l, int inst){
	char* res = malloc(sizeof(char) * 100);
	for(int i = 0; i < l.i ; i++){
		sprintf(res, "%d", inst);
		(CODE.items[l.items[i]]).res = res;
	}
}

/* Funcion que imprime las cuadruplas. */
void print_code(){
    printf("\n*** CODIGO INTERMEDIO ***\n");
    printf("inst\top\targ1\targ2\tres\n");
    for(int i = 0; i < CODE.i; i++){
        printf("%d\t%s\t%s\t%s\t%s\n",i, CODE.items[i].op, CODE.items[i].arg1, CODE.items[i].arg2, CODE.items[i].res);
    }
}